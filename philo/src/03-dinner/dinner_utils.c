/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:35:08 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 03:51:29 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SPINLOCK to synchronize philos start

/*
	1. wait alll philos
	2. sychnronize all
	3. endless loop philo
*/

#include "../include/philo.h"

void	delay_time(long usec, t_table *table);

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
		set_bool(&philo->philo_mutex, &philo->full_meals, true);

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

void	delay_time(long usec, t_table *table)
{
	long	start;
	long	passed;
	long	remain;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (sim_finished(table))
			break ;
		passed = gettime(MICROSECOND) - start;
		remain = usec - passed;
		if (remain > 1000)
			usleep(remain / 2);
		else
			while (gettime(MICROSECOND) - start < usec)
				usleep(10);
	}
}

// TO-DO: THINK
// void	think(t_philo *philo, bool is_inital_phase)
// {
// 	long	t_eat;
// 	long	t_sleep;
// 	long	t_think;

// 	if (!is_inital_phase)
// 		print_status(philo, THINK);
// 	if (philo->info->num_philos % 2 == 0)
// 		return ;
// 	t_eat = philo->info->time_to_eat;
// 	t_sleep = philo->info->time_to_sleep;
// 	t_think = t_eat * 2 - t_sleep;
// 	if (t_think < 0)
// 		t_think = 0;
// 	delay_time(t_think * 0.5, philo->info);
// }

void	usleep_micro(long time_to_sleep)
{
	long	start_time;

	start_time = gettime(MICROSECOND);      // get current time in microseconds
	if (time_to_sleep > 1000000L)        // optional: for long sleeps, first half
		usleep(time_to_sleep / 2);
	else
		usleep(time_to_sleep / 2);       // for short sleeps, same logic

	while (gettime(MICROSECOND) < start_time + time_to_sleep)
		usleep(50);                         // fine-tune with small sleeps
}

// gettimeofday
// time_code -> SECONDS MILIESECONDS MICROSECONDS
// chronometer?

long gettime(t_time_type type)
{
    struct  timeval tv;
    
    if (gettimeofday(&tv, NULL))
        error_msg("ERROR: gettimeofday failed");
    if (type == SECOND)
        return(tv.tv_sec + (tv.tv_usec / 1000000));
    if (type == MILISECOND)
        return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    if (type == MICROSECOND)
        return((tv.tv_sec * 1000000) + tv.tv_usec); 
    else
    {
        error_msg("ERROR: gettimeofday failed");
        return (0);
    }
}
