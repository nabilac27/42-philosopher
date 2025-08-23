/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:59:56 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 15:08:31 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	first_fork_order(t_philo *philo, t_mutex *first_fork,
		t_mutex *second_fork)
{
	handle_mutex(first_fork, LOCK);
	log_status(philo, "has taken a fork");
	handle_mutex(second_fork, LOCK);
	log_status(philo, "has taken a fork");
}

void	lock_forks(t_philo *philo)
{
	t_table			*table;
	unsigned long	now;
	unsigned long	hunger;
	bool			is_critical;

	table = philo->table;
	if (table->end_sim)
		return ;
	now = gettime(MILISECOND);
	hunger = now - philo->last_meal_time;
	is_critical = hunger >= (table->time_to_die * 3 / 4);
	if (is_critical)
		usleep(1000);
	else if (philo->philo_id % 2 == 0)
		usleep(table->time_to_eat / 4);
	else
		usleep(50);
	if (philo->philo_id % 2 == 0)
		first_fork_order(philo, &philo->right_fork->fork,
			&philo->left_fork->fork);
	else
		first_fork_order(philo, &philo->left_fork->fork,
			&philo->right_fork->fork);
}

void	eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (table->end_sim)
		return ;
	lock_forks(philo);
	if (table->end_sim)
	{
		handle_mutex(&philo->left_fork->fork, UNLOCK);
		handle_mutex(&philo->right_fork->fork, UNLOCK);
		return ;
	}
	handle_mutex(&philo->philo_mutex, LOCK);
	philo->last_meal_time = gettime(MILISECOND);
	philo->count_eaten_meals++;
	if (table->num_must_meals > 0
		&& philo->count_eaten_meals >= table->num_must_meals)
		philo->is_full = true;
	handle_mutex(&philo->philo_mutex, UNLOCK);
	log_status(philo, "is eating");
	precise_sleep(table->time_to_eat, table);
	handle_mutex(&philo->left_fork->fork, UNLOCK);
	handle_mutex(&philo->right_fork->fork, UNLOCK);
}

void	sleep_philo(t_philo *philo)
{
	if (philo->table->end_sim)
		return ;
	log_status(philo, "is sleeping");
	precise_sleep(philo->table->time_to_sleep, philo->table);
}

void	think(t_philo *philo)
{
	t_table			*table;
	unsigned long	now;
	unsigned long	time_since_last_meal;
	unsigned long	safe_think_time;

	table = philo->table;
	log_status(philo, "is thinking");
	now = gettime(MILISECOND);
	time_since_last_meal = now - philo->last_meal_time;
	safe_think_time = 0;
	if (table->time_to_die > time_since_last_meal + 50)
	{
		safe_think_time = (table->time_to_die - time_since_last_meal) / 2;
		if (safe_think_time > table->time_to_eat / 2)
			safe_think_time = table->time_to_eat / 2;
		if (safe_think_time < 20)
			safe_think_time = 20;
		usleep(safe_think_time * 1000);
	}
}
