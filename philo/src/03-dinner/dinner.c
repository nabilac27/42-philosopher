/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:52:23 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/20 05:21:09 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	no meals = return 0
	if only one philo = ad hoc function
	1.) create all threads, all philos
	2.) create monitor thread
	3.) sycnhronize the beginning of sim
		pthread_create -> philo starts running
		every philo start simultaneously
	4.) JOIN everyone
*/

void	*philo_1(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	handle_mutex(&philo->table->table_mutex, LOCK);
	philo->table->num_threads_running++;
	handle_mutex(&philo->table->table_mutex, UNLOCK);
	print_status(philo, TAKE_LEFT_FORK);
	while (!sim_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	dinner(t_table *table)
{
    t_thread_type	create_type;
    t_thread_type	join_type;
    int				i;

    create_type = CREATE;
    join_type = JOIN;
    i = 0;
    if (table->num_philos == 1)
        handle_thread(&(table->philos[0].thread_id), philo_1,
            &table->philos[0], &create_type);
    else
    {
        while (i < table->num_philos)  // Changed i++ to i
        {
            handle_thread(&(table->philos[i].thread_id), routine_sim,
                &table->philos[i], &create_type);
            i++;  // Move increment after the thread creation
        }
    }
    // Set simulation start time before creating threads
    table->start_sim = gettime(MILISECOND);
    // Monitor the simulation
    handle_thread(&table->monitor, dinner_monitor, table, &create_type);
    set_bool(&table->table_mutex, &table->threads_ready, true);
    // NOW ALL THREADS READY (wait_all_threads)
    // Removed duplicate line
    // Wait for everyone - only if we have multiple philosophers
    if (table->num_philos > 1)
    {
        i = 0;
        while (i < table->num_philos)
        {
            handle_thread(&table->philos[i].thread_id, NULL, NULL, &join_type);
            i++;
        }
    }
    // if reach this means all philos are full
    set_bool(&table->table_mutex, &table->end_sim, true);
    handle_thread(&table->monitor, NULL, NULL, &join_type);
}

// if even, wait ensures not all even philo pick fork at the same time
// if odd, odd philo execute think in inital phase
void	initial_delay(t_philo *philo)
{
	if (philo->table->num_philos % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			delay_time(30000, philo->table);
	}
	else
	{
		if (philo->philo_id % 2)
			think(philo, true);
	}
}

void	*routine_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// spinlock
	wait_all_threads(philo->table); // TO-DO;
	// synchro with monitor
	// Remove dinner_monitor call from routine_sim, only monitor thread should run it
	// increase table variable coutner, with all threads running
	// set last meal time
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	handle_mutex(&philo->table->table_mutex, LOCK);
	philo->table->num_threads_running++;
	handle_mutex(&philo->table->table_mutex, UNLOCK);
	initial_delay(philo);
	while (!(sim_finished(philo->table)))
	{
		if (philo->full_meals) // to-do: thread safe?
			break ;
		eat(philo);
		sleeps(philo);
		think(philo, false);
	}
	return (NULL);
}

void	*dinner_monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	// make sure all philo runs
	// spinlock untill all thread run
	while (!is_all_threads_running(&table->table_mutex,
			table->num_threads_running, &table->num_philos))
		usleep(10);
	// check time to die constantly
	while (!sim_finished(table))
	{
		i = 0;
		while (i < table->num_philos && !sim_finished(table))
		{
			if (is_dead_philo(&table->philos[i]))
			{
				set_bool(&table->table_mutex, &table->end_sim, true);
				print_status(&table->philos[i], DEAD);
				break ;
			}
			i++;
		}
		usleep(10);
	}
	return (NULL);
}

bool	is_dead_philo(t_philo *philo)
{
	long	elapsed;
	long	time_to_die_ms;

	if (get_bool(&philo->philo_mutex, &philo->full_meals))
		return (false);
	elapsed = gettime(MILISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die_ms = philo->table->time_to_die;
	if (elapsed > time_to_die_ms)
		return (true);
	return (false);
}

void	print_status(t_philo *philo, t_philo_status status)
{
	long	time;

	time = gettime(MILISECOND) - (philo->table->start_sim);
	if (philo->full_meals)
		return ;
	handle_mutex(&philo->table->print_mutex, LOCK);
	if ((status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK)
		&& !sim_finished(philo->table))
		printf("%ld %ld has taken a fork\n", time, philo->philo_id);
	else if ((status == EAT) && !sim_finished(philo->table))
		printf("%ld %ld is eating\n", time, philo->philo_id);
	else if ((status == SLEEP) && !sim_finished(philo->table))
		printf("%ld %ld is sleeping\n", time, philo->philo_id);
	else if ((status == THINK) && !sim_finished(philo->table))
		printf("%ld %ld is thinking\n", time, philo->philo_id);
	else if ((status == DEAD) && !sim_finished(philo->table))
		printf("%ld %ld is died\n", time, philo->philo_id);
	handle_mutex(&philo->table->print_mutex, UNLOCK);
}
