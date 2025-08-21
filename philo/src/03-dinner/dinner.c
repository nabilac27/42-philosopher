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
	// Monitor the simulation
	handle_thread(&table->monitor, monitor_dinner, table, CREATE);


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

	// // if reach this means all philos are full
	set_bool(&table->table_mutex, &table->end_simulation, true);
	handle_thread(&table->monitor, NULL, NULL, JOIN);
}

void *dinner_monitor(void *data)
{
    t_table *table;

    table = (t_table *)data;

    
    
}
