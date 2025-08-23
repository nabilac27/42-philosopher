/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:13:11 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 11:55:14 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	take_forks(t_philo *philo)
{
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
}

static void	release_forks(t_philo *philo)
{
	handle_mutex(&philo->left_fork->fork, UNLOCK);
	handle_mutex(&philo->right_fork->fork, UNLOCK);
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	take_forks(philo);
	handle_mutex(&philo->philo_mutex, LOCK);
	philo->last_meal_time = gettime(MILISECOND);
	philo->count_eaten_meals++;
	if (table->num_must_meals > 0
		&& philo->count_eaten_meals >= table->num_must_meals)
		philo->is_full = true;
	handle_mutex(&philo->philo_mutex, UNLOCK);
	log_status(philo, "is eating");
	precise_sleep(table->time_to_eat);
	release_forks(philo);
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

static void	wait_for_all_threads_ready(t_philo *philo)
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
	while (!table->is_all_threads_ready)
		usleep(100);
}

static void	run_single_philosopher(t_philo *philo)
{
	handle_mutex(&philo->left_fork->fork, LOCK);
	log_status(philo, "has taken a fork");
	precise_sleep(philo->table->time_to_die);
	handle_mutex(&philo->left_fork->fork, UNLOCK);
}

void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_table *table = philo->table;

	wait_for_all_threads_ready(philo);

	if (table->num_philos == 1)
	{
		run_single_philosopher(philo);
		return (NULL);
	}

	if (philo->philo_id % 2 == 0)
		usleep(2000);

	while (!table->end_sim && !philo->is_full)
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
