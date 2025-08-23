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
        while (i < table->num_philos)
        {
            handle_thread(&(table->philos[i].thread_id), routine_sim,
                &table->philos[i], &create_type);
            i++;
        }
    }
    // Set simulation start time before creating threads
    table->start_sim = gettime(MILISECOND);
    // Monitor the simulation
    handle_thread(&table->monitor, dinner_monitor, table, &create_type);
    set_bool(&table->table_mutex, &table->is_all_threads_ready, true);
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
    set_bool(&table->table_mutex, &table->is_routine_finished, true);
    handle_thread(&table->monitor, NULL, NULL, &join_type);
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
		if (philo->is_full) // to-do: thread safe?
			break ;
		eat(philo);
		sleeps(philo);
		think(philo, false);
	}
	return (NULL);
}
