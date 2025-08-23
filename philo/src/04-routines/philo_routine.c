/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:13:11 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 10:10:59 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	// 1️⃣ Take forks
	if (philo->philo_id % 2 == 0)
	{
		handle_mutex(&philo->right_fork->fork, LOCK);
		log_status(philo, "has taken a fork");
		handle_mutex(&philo->left_fork->fork, LOCK);
		log_status(philo, "has taken a fork");
	}
	else
	{
		handle_mutex(&philo->left_fork->fork, LOCK);
		log_status(philo, "has taken a fork");
		handle_mutex(&philo->right_fork->fork, LOCK);
		log_status(philo, "has taken a fork");
	}
	// 2️⃣ Eat
	handle_mutex(&philo->philo_mutex, LOCK);
	philo->last_meal_time = gettime(MILISECOND);
	philo->count_eaten_meals++;
	if (table->num_must_meals > 0
		&& philo->count_eaten_meals >= table->num_must_meals)
		philo->is_full = true;
	handle_mutex(&philo->philo_mutex, UNLOCK);
	log_status(philo, "is eating");
	precise_sleep(table->time_to_eat);
	// 3️⃣ Release forks
	handle_mutex(&philo->left_fork->fork, UNLOCK);
	handle_mutex(&philo->right_fork->fork, UNLOCK);
}

void	sleep_philo(t_philo *philo)
{
	log_status(philo, "is sleeping");
	precise_sleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	log_status(philo, "is thinking");
}

void	wait_for_all_threads_ready(t_table *table)
{
	// Increment ready count safely
	handle_mutex(&table->table_mutex, LOCK);
	table->num_threads_ready++;
	if (table->num_threads_ready == table->num_philos)
		table->is_all_threads_ready = true;
	handle_mutex(&table->table_mutex, UNLOCK);
	// Wait until all threads are ready
	while (!table->is_all_threads_ready)
		usleep(100); // short sleep to avoid busy waiting
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	wait_for_all_threads_ready(table);
	handle_mutex(&philo->philo_mutex, LOCK);
    philo->last_meal_time = gettime(MILISECOND);
    handle_mutex(&philo->philo_mutex, UNLOCK);
	initial_delay(philo);
	while (!(table->end_sim) && !(philo->is_full))
	{
		eat(philo);         // take forks, eat, release forks
		sleep_philo(philo); // sleep + log
		think(philo);       // think + log
	}
	return (NULL);
}
