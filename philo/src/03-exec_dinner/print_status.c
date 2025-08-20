/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 05:05:03 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/20 05:17:35 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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