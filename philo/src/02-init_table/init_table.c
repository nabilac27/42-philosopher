/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 19:49:03 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/19 21:22:03 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void init_table(t_table *table)
{
    int i;

    i = 0;
    table->end_sim = false;
    table->prep_start_sim = false;
        
    table->philos = handle_malloc(table->num_philos);
    table->forks = handle_malloc(table->num_philos);
    init_philo(table);
    handle_mutex(&table->table_mutex, INIT);
    while(i++ < table->num_philos)
    {
        table->forks[i].fork_id = i;
        handle_mutex(&table->forks[i].fork, INIT);
    }
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
        init_forks(philo, table->forks, i);
    }
}

// first fork: left, second fork: right
void init_forks(t_philo *philo, t_fork *fork, int philo_pos)
{
    // int num_philos;
    // num_philos = philo->table->num_philos;
    
    philo->left_fork = &fork[(philo_pos + 1) % 2];
    philo->right_fork = &fork[philo_pos];
    // TO AVOID DEADLOCK
    if (philo->philo_id % 2)
    {
        philo->left_fork = &fork[philo_pos];
        philo->right_fork = &fork[(philo_pos + 1) % 2];
    }
}

void *handle_malloc(size_t bytes)
{
    void *ret_value;
    
    ret_value = malloc(bytes);
    if (ret_value == NULL)
        error_msg("ERROR: malloc failed");
    return(ret_value);
}
