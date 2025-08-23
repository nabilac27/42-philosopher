/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_times.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 04:17:46 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 04:41:57 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// if even, wait ensures not all even philo pick fork at the same time
// if odd, odd philo execute think in inital phase

void	initial_delay(t_philo *philo)
{
	if (philo->table->num_philos % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			delay_time(30000, philo->table);
	}
	else
	{
		if (philo->philo_id % 2)
			think(philo, true);
	}
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
