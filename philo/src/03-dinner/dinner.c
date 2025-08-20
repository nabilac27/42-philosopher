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

void	dinner(t_table *table)
{
	t_thread_type create_type = CREATE;
	t_thread_type join_type = JOIN;

	int	i;

	i = 0;
	if (table->num_must_meals == 0)
		return ;
	else if (table->num_philos == 1)
	{
		// Special case for single philosopher
		printf("0 1 has taken a fork\n");
		usleep_micro(table->time_to_die * 1000);
		printf("%ld 1 died\n", table->time_to_die);
		return ;
	}
	// TODO: Monitor
	else
	{
		while (i < table->num_philos)				
		{
			handle_thread(&table->philos[i].thread_id, routine_sim,
			&table->philos[i], &create_type);
			i++;
		}
		
		// start of simulation
		table->start_sim = gettime(MILISECOND);
		
		// NOW ALL THREADS READY (wait_all_threads)
		set_bool(&table->table_mutex, &table->threads_ready, true);
		
		// Monitor the simulation
		monitor_simulation(table);
	};

	// Wait for everyone - only if we have multiple philosophers
	if (table->num_philos > 1)
	{
		i = 0;
		while(i < table->num_philos)
		{
			handle_thread(&table->philos[i].thread_id, NULL, NULL, &join_type);
			i++;
		}
	}

	// if reach this means all philos are full
}

/*
	1. wait alll philos
	2. sychnronize all
	3. endless loop philo
*/
void	*routine_sim(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

    // spinlock
	wait_all_threads(philo->table); // TO-DO;

	// set last meal time
	while (!(sim_finished(philo->table)))
	{
		if (philo->full_meals) // to-do: thread safe?
			break;

		eat(philo);
		print_status(philo, SLEEP);
		usleep_micro(philo->table->time_to_sleep);
	
		think(philo);
	}
	return (NULL);
}

void eat(t_philo *philo)
{
	// 1
	handle_mutex(&philo->left_fork->fork, LOCK);
	print_status(philo, TAKE_LEFT_FORK);
	handle_mutex(&philo->right_fork->fork, LOCK);
	print_status(philo, TAKE_RIGHT_FORK);

	// 2
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	philo->count_eaten_meals++;
	print_status(philo, EAT);
	usleep_micro(philo->table->time_to_eat);

	if((philo->table->num_must_meals > 0 && philo->count_eaten_meals) == philo->table->num_must_meals)
		set_bool(&philo->philo_mutex, &philo->full_meals, true);

	// 3
	handle_mutex(&philo->left_fork->fork, UNLOCK);
	handle_mutex(&philo->right_fork->fork, UNLOCK);
}

void think(t_philo *philo)
{
	print_status(philo, THINK);
}