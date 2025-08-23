/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:35:08 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 04:41:26 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SPINLOCK to synchronize philos start

/*
	1. wait alll philos
	2. sychnronize all
	3. endless loop philo
*/

#include "../include/philo.h"

void eat(t_philo *philo)
{
	// 1
	handle_mutex(&philo->left_fork->fork, LOCK);
	print_status(philo, TAKE_LEFT_FORK);
	handle_mutex(&philo->right_fork->fork, LOCK);
	print_status(philo, TAKE_RIGHT_FORK);

	// 2
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	philo->count_eaten_meals++;
	print_status(philo, EAT);
	usleep_micro(philo->table->time_to_eat);

	if((philo->table->num_must_meals > 0 && philo->count_eaten_meals) == philo->table->num_must_meals)
		set_bool(&philo->philo_mutex, &philo->is_full, true);

	// 3
	handle_mutex(&philo->left_fork->fork, UNLOCK);
	handle_mutex(&philo->right_fork->fork, UNLOCK);
}

void	think(t_philo *philo, bool is_initial)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!is_initial)
		print_status(philo, THINK);
	if (philo->table->num_philos % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	delay_time(t_think * 0.5, philo->table);
}


void sleeps(t_philo *philo)
{
	usleep_micro(philo->table->time_to_sleep);
	print_status(philo, SLEEP);
}

void	*philo_1(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECOND));
	handle_mutex(&philo->table->table_mutex, LOCK);
	philo->table->num_threads_running++;
	handle_mutex(&philo->table->table_mutex, UNLOCK);
	print_status(philo, TAKE_LEFT_FORK);
	while (!sim_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	print_status(t_philo *philo, t_philo_status status)
{
	long	time;

	time = gettime(MILISECOND) - (philo->table->start_sim);
	if (philo->is_full)
		return ;
	handle_mutex(&philo->table->print_mutex, LOCK);
	if ((status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK)
		&& !sim_finished(philo->table))
		printf("%ld %ld has taken a fork\n", time, philo->philo_id);
	else if ((status == EAT) && !sim_finished(philo->table))
		printf("%ld %ld is eating\n", time, philo->philo_id);
	else if ((status == SLEEP) && !sim_finished(philo->table))
		printf("%ld %ld is sleeping\n", time, philo->philo_id);
	else if ((status == THINK) && !sim_finished(philo->table))
		printf("%ld %ld is thinking\n", time, philo->philo_id);
	else if ((status == DEAD) && !sim_finished(philo->table))
		printf("%ld %ld is died\n", time, philo->philo_id);
	handle_mutex(&philo->table->print_mutex, UNLOCK);
}
