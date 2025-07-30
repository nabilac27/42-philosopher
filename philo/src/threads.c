/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:19:00 by nchairun          #+#    #+#             */
/*   Updated: 2025/07/30 13:37:06 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*thread_monitor(void *table);
void	*thread_routine(void *table);

bool	setup_thread(t_table *table)
{
	pthread_t	monitor_thread;
	int			i;

	// monitor thread
	if (pthread_create(&monitor_thread, NULL, &thread_monitor, table) != 0)
		return (false);

	// philosopher threads
	i = 0;
	while (i < (table->num_philos))
	{
		if (pthread_create(&table->philos[i].thread, NULL, &thread_routine, &table->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(table->philos[i].thread, NULL);
			pthread_join(monitor_thread, NULL);
			return (false);
		}
		i++;
	}

	// Wait for monitor thread to finish
	if (pthread_join(monitor_thread, NULL) != 0)
		return (false);
	
	// Join philosopher threads
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (true);
}

void	*thread_monitor(void *table)
{
   t_table *p_table = (t_table *)table;
	
	while (table != NULL)
	{
		if (meal_round_finished() || philo_died())
			break ;
	}
	printf("thread_monitor\n");
	return(p_table);
}

void	*thread_routine(void *philo)
{
	t_philo *p_philo = (t_philo *)philo;
	printf("Philosopher %d is thinking...\n", p_philo->id);
	usleep(1000 * 500);  // 500 ms
	printf("Philosopher %d is done.\n", p_philo->id);
	return NULL;
}

bool	meal_round_finished(t_data *table)
{

}
