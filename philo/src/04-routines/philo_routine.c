/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:13:11 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 10:54:09 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	take_forks(t_philo *philo)
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
	handle_mutex(&philo->left_fork->fork, UNLOCK);
	handle_mutex(&philo->right_fork->fork, UNLOCK);
}


void	sleep_philo(t_philo *philo)
{
	log_status(philo, "is sleeping");
	precise_sleep(philo->table->time_to_sleep);
}

void	wait_for_all_threads_ready(t_table *table)
{
	handle_mutex(&table->table_mutex, LOCK);
	table->num_threads_ready++;
	table->philos->last_meal_time = gettime(MILISECOND);
	if (table->num_threads_ready == table->num_philos)
		table->is_all_threads_ready = true;
	handle_mutex(&table->table_mutex, UNLOCK);
	while (!table->is_all_threads_ready)
		usleep(100);
}

// void	*philo_routine(void *arg)
// {
// 	t_philo	*philo;
// 	t_table	*table;

// 	philo = (t_philo *)arg;
// 	table = philo->table;
// 	wait_for_all_threads_ready(table);
// 	initial_delay(philo);
// 	while (!(table->end_sim) && !(philo->is_full))
// 	{
// 		eat(philo);
// 		sleep_philo(philo);
// 		log_status(philo, "is thinking");
// 	}
// 	return (NULL);
// }

void	count_ready_threads(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->table->num_threads_ready++;
	pthread_mutex_unlock(&philo->table->table_mutex);
}

int	count_threds_to_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_mutex);
	if (philo->table->num_threads_ready == philo->table->num_philos)
	{
		pthread_mutex_unlock(&philo->table->table_mutex);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->table_mutex);
		return (false);
	}
}

void	*philo_routine(void *arg)
{	
	t_philo	*philo;

	philo = (t_philo *)arg;
	count_ready_threads(philo);
	while (count_threds_to_philo(philo) == false)
	{
		usleep(42);
	}
	if (philo->table->num_philos == 1)
	{
		log_status(philo, "has taken a fork");
		return (philo);
	}
	if (philo->philo_id % 2 == 0)
		usleep(2000);
	while(1)
	{
		eat(philo);
		sleep_philo(philo);
		log_status(philo, "is thinking");
	}
	return (philo);
}
