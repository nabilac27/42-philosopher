/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:23:06 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 10:09:41 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	monitor_died(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		handle_mutex(&table->philos[i].philo_mutex, LOCK);
		if (!(table->philos[i].is_full && (gettime(MILISECOND)
					- table->philos[i].last_meal_time) > table->time_to_die))
		{
			log_status(&table->philos[i], "died");
			table->end_sim = true;
			handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
			return (true);
		}
		handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
		i++;
	}
	return (false);
}

static bool	monitor_full(t_table *table)
{
	int	i;
	int	full_count;

	full_count = 0;
	i = 0;
	while (i < table->num_philos)
	{
		handle_mutex(&table->philos[i].philo_mutex, LOCK);
		if (table->philos[i].is_full)
			full_count++;
		handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
		i++;
	}
	if (full_count == table->num_philos)
	{
		table->end_sim = true;
		return (true);
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!table->is_all_threads_ready)
		usleep(100);
	while (!table->end_sim)
	{
		if (monitor_died(table))
			return (NULL);
		if (monitor_full(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	log_status(t_philo *philo, const char *status)
{
	t_table	*table;

	table = philo->table;
	handle_mutex(&table->print_mutex, LOCK);
	if (!table->end_sim)
		printf("%ld %ld %s\n", gettime(MILISECOND) - table->start_sim,
			philo->philo_id, status);
	handle_mutex(&table->print_mutex, UNLOCK);
}
