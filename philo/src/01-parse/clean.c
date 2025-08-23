/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 04:12:40 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 08:40:23 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_msg(char *msg)
{
	printf("%s \n", msg);
	exit(1);
}

void clean(t_table *table)
{
    t_philo *philo;
    int i;

    i = 0;
    while (i < table->num_philos)
    {
        philo = &table->philos[i];
        handle_mutex(&philo->philo_mutex, DESTROY);
        i++;
    }

    i = 0;
    while (i < table->num_philos)
    {
        handle_mutex(&table->forks[i].fork, DESTROY);
        i++;
    }

    handle_mutex(&table->print_mutex, DESTROY);
    handle_mutex(&table->table_mutex, DESTROY);

    free(table->philos);
    free(table->forks);
}
