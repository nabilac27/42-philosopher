/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:00:32 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 12:28:17 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	handle_thread(pthread_t *thread, void *(*routine)(void *), void *data,
		t_thread_type type)
{
	int	status;

	status = 0;
	if (type == CREATE)
		status = pthread_create(thread, NULL, routine, data);
	else if (type == JOIN)
		status = pthread_join(*thread, NULL);
	else if (type == DETACH)
		status = pthread_detach(*thread);
	else
		error_msg("ERROR: handle_thread - invalid type");
	if (status != 0)
		error_msg("ERROR: thread operation failed");
}

void	init_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		handle_thread(&table->philos[i].thread_id, philo_routine,
			&table->philos[i], CREATE);
		i++;
	}
	table->philos->last_meal_time = gettime(MILISECOND);
}

void	init_monitor_thread(t_table *table)
{
	handle_thread(&table->monitor, monitor_routine, table, CREATE);
	table->philos->last_meal_time = gettime(MILISECOND);
}

void	wait_all_philo_threads_finish(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		handle_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}

void	wait_monitor_thread_finish(t_table *table)
{
	handle_thread(&table->monitor, NULL, NULL, JOIN);
}
