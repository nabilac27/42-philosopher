/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:23:06 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 15:14:32 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	all_philos_full(t_table *table)
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

bool	check_philo_died(t_table *table)
{
	int				i;
	unsigned long	now;

	i = 0;
	while (i < table->num_philos && !(table->end_sim))
	{
		handle_mutex(&table->philos[i].philo_mutex, LOCK);
		now = gettime(MILISECOND);
		if (!(table->philos[i].is_full) && (now
				- table->philos[i].last_meal_time) >= table->time_to_die)
		{
			log_status(&table->philos[i], "died");
			table->philo_dead = true;
			table->end_sim = true;
			handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
			printf("Philosopher %ld died, ending simulation.\n",
				table->philos[i].philo_id);
			return (true);
		}
		handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
		i++;
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_table			*table;
	int				i;
	unsigned long	now;

	table = (t_table *)arg;
	while (!(table->is_all_threads_ready))
		usleep(100);
	while (!(table->end_sim))
	{
		if (all_philos_full(table))
			break ;
		if (check_for_deaths(table))
			return (NULL);
	}
	usleep(50);
	return (NULL);
}

void	log_status(t_philo *philo, const char *status)
{
	t_table	*table;
	long	now;

	table = philo->table;
	handle_mutex(&table->print_mutex, LOCK);
	if (!(table->end_sim))
	{
		now = gettime(MILISECOND);
		printf("%ld %ld %s\n", now - table->start_sim, philo->philo_id, status);
	}
	handle_mutex(&table->print_mutex, UNLOCK);
}
