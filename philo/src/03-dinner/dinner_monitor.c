/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 04:22:01 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 04:41:03 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
				set_bool(&table->table_mutex, &table->is_routine_finished, true);
				print_status(&table->philos[i], DEAD);
				break ;
			}
			i++;
		}
		usleep(10);
	}
	return (NULL);
}

bool	sim_finished(t_table *table)
{
    return(get_bool(&table->table_mutex, &table->is_routine_finished));
}

bool	is_dead_philo(t_philo *philo)
{
	long	elapsed;
	long	time_to_die_ms;

	if (get_bool(&philo->philo_mutex, &philo->is_full))
		return (false);
	elapsed = gettime(MILISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	time_to_die_ms = philo->table->time_to_die;
	if (elapsed > time_to_die_ms)
		return (true);
	return (false);
}
