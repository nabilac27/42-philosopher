/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:21:26 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 10:31:45 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// void	initial_delay(t_philo *philo)
// {
// 	if (philo->table->num_philos % 2 == 0)
// 	{
// 		if (philo->philo_id % 2 == 0)
// 			delay_time(30000, philo->table);
// 	}
// 	else
// 	{
// 		if (philo->philo_id % 2)
// 			log_status(philo, "is thinking");
// 	}
// }

void initial_delay(t_philo *philo)
{
    if (philo->philo_id % 2 == 0)
        usleep(100);
}

long	gettime(t_time_type type)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_msg("ERROR: gettimeofday failed");
	if (type == MILISECOND)
		return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
	if (type == MICROSECOND)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		error_msg("ERROR: gettimeofday failed");
	return (0);
}

void	delay_time(long usec, t_table *table)
{
	long	start;
	long	passed;
	long	remain;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (table->end_sim)
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

void	precise_sleep(long duration_us)
{
	long	start;

	start = gettime(MILISECOND);
	while ((gettime(MILISECOND) - start) < duration_us / 1000)
		usleep(50);
}

long	get_elapsed_time(t_table *table)
{
	return (gettime(MILISECOND) - table->start_sim);
}
