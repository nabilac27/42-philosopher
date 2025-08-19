/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 20:52:23 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/19 21:17:04 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
    no meals = return 0
    if only one philo = ad hoc function
    1.) create all threads, all philos
    2.) create monitor thread
    3.) sycnhronize the beginning
    4.) JOIN everyone
*/

void    exec_dinner(t_table *table)
{
    int i;

    i = 0;
    
    if (table->num_must_meals = 0)
        return;
    else if (table->num_must_meals = 1)
        // TO-DO
    else
    {
        while (i++ < table->num_philos)
            handle_thread(&table->philos[i].thread_id, dinner_sim, &table->philos[i], CREATE);
    }
        // NOW ALL THREADS READY (PREP_START_SIM)
        // setter, getter
}

/*
    1. wait alll philos
    2. sychnronize all
    3. endless loop philo
*/
void   *dinner_sim(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;

    prep_start_sim(philo->table); // TO-DO;
    
    return(NULL);
}