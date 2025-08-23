/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:13:11 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 15:09:04 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	single_philo(t_philo *philo)
{
	handle_mutex(&philo->left_fork->fork, LOCK);
	log_status(philo, "has taken a fork");
	precise_sleep(philo->table->time_to_die, philo->table);
	handle_mutex(&philo->left_fork->fork, UNLOCK);
}

void	wait_for_all_threads_ready(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	handle_mutex(&table->table_mutex, LOCK);
	philo->last_meal_time = gettime(MILISECOND);
	table->num_threads_ready++;
	if (table->num_threads_ready == table->num_philos)
	{
		table->is_all_threads_ready = true;
		table->start_sim = gettime(MILISECOND);
	}
	handle_mutex(&table->table_mutex, UNLOCK);
	while (!(table->is_all_threads_ready))
		usleep(100);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	wait_for_all_threads_ready(philo);
	if (table->num_philos == 1)
	{
		single_philo(philo);
		return (NULL);
	}
	if (philo->philo_id % 2 == 0)
		usleep(5000);
	while (!(table->end_sim) && !(philo->is_full))
	{
		eat(philo);
		if (table->end_sim || philo->is_full)
			break ;
		sleep_philo(philo);
		if (table->end_sim || philo->is_full)
			break ;
		think(philo);
	}
	return (NULL);
}
