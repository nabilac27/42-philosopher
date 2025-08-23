/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 04:12:40 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 04:13:00 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_msg(char *msg)
{
	printf("%s \n", msg);
	exit(1);
}

void    clean(t_table   *table)
{
    t_philo *philo;
    int     i;

    i = 0;
    while (i++ < table->num_philos)
    {
        philo = table->philos + i;
        handle_mutex(&philo->philo_mutex, DESTROY);
    }
    handle_mutex(&table->print_mutex, DESTROY);
    handle_mutex(&table->table_mutex, DESTROY);
    free(table->forks);
    free(table->philos);
}