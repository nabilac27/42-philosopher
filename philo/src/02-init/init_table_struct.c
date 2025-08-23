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

void	init_forks_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		table->forks[i].fork_id = i;
		handle_mutex(&table->forks[i].fork, INIT);
		i++;
	}
}

void	init_table_mutex(t_table *table)
{
	handle_mutex(&table->table_mutex, INIT);
	handle_mutex(&table->print_mutex, INIT);
}

void	init_table_struct(t_table *table)
{
	int	i;

	i = 0;
	table->end_sim = false;
	table->is_all_threads_ready = false;
	table->num_threads_ready = 0;
	table->philos = handle_malloc(sizeof(t_philo) * table->num_philos);
	table->forks = handle_malloc(sizeof(t_fork) * table->num_philos);
	init_table_mutex(table);
	init_forks_mutex(table);
	init_philo_struct(table);
}
