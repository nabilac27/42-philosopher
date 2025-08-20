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
	int	i;

	i = 0;
	if (table->num_must_meals = 0)
		return ;
	else if (table->num_philos == 1);
		
	else
	{
		while (i++ < table->num_philos)				
		{
			handle_thread(&table->philos[i].thread_id, routine_sim,
			&table->philos[i], CREATE);
		}
		
	}
	// start of simulation
	table->start_sim = gettime(MILISECOND);
	
	// NOW ALL THREADS READY (wait_all_threads)
    set_bool(&table->table_mutex, &table->threads_ready, true);

	// Wait for everyone
	i = 0;

	while(i++ < table->num_philos)
		handle_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);

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

		// to-do eat
		// TO-DO SLEEP : write status, precise usleep
		print_status(philo, SLEEP);
		usleep_micro(philo->table->time_to_sleep);
		
		// to-do think
	}
	return (NULL);
}
