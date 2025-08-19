/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:49:03 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/19 20:05:50 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void init_data(t_table *table)
{
    table->end_sim = false;
    table->philos = malloc(sizeof(t_philo) * table->num_philos);
    table->forks = malloc(sizeof(t_fork) * table->num_philos);
	if (!table)
		return (NULL);
    
}

void init_philo(t_table *table)
{
    t_philo *philo;
    
    int i;

    i = 0;

    while (i < table->num_philos)
    {
        philo = table->philos + i;
        philo->philo_id = i + 1;
        philo->full_meals = false;
        philo->count_eaten_meals = 0;
        philo->table = table;
        i++;

        init_forks();
    }
}