/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:35:08 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/20 23:06:16 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SPINLOCK to synchronize philos start

#include "../include/philo.h"

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

void    wait_all_threads(t_table *table)
{
    while(!(get_bool(&table->table_mutex, &table->threads_ready)))
    ;
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
        return((tv.tv_sec + 1000) + (tv.tv_usec / 1000));
    if (type == MICROSECOND)
        return((tv.tv_sec + 1000000) + tv.tv_usec); 
    else
         error_msg("ERROR: gettimeofday failed");   
}

void    print_status(t_philo *philo, t_philo_status status)
{
    long    time;
    
    time = gettime(MILISECOND) - (philo->table->start_sim);

    if (philo->full_meals)
        return;
        
    handle_mutex(&philo->table->print_mutex, LOCK);
    
    if ((status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK) && !sim_finished(philo->table))
        printf("%ld %d has taken a fork\n", time, philo->philo_id);
    else if ((status == EAT) && !sim_finished(philo->table))
        printf("%ld %d is eating\n", time, philo->philo_id);
    else if ((status == SLEEP) && !sim_finished(philo->table))
        printf("%ld %d is sleeping\n", time, philo->philo_id);
    else if ((status == THINK) && !sim_finished(philo->table))
        printf("%ld %d is thinking\n", time, philo->philo_id);
    else if ((status == DEAD) && !sim_finished(philo->table))
        printf("%ld %d is died\n", time, philo->philo_id);
        
    handle_mutex(&philo->table->print_mutex, UNLOCK);
}
