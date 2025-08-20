/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:35:08 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/20 04:57:01 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SPINLOCK to synchronize philos start

#include "../include/philo.h"

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