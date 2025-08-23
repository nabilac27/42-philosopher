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

void	init_table(t_table *table)
{
	int	i;

	i = 0;
	table->end_sim = false;
	table->threads_ready = false;
	table->num_threads_ready = 0;
	table->philos = handle_malloc(sizeof(t_philo) * table->num_philos);
	table->forks = handle_malloc(sizeof(t_fork) * table->num_philos);

	if (table->num_philos < 1 || table->time_to_die < 1 || table->time_to_eat < 1
		|| table->time_to_sleep < 1)
		error_msg("ERROR: init_table()");

	handle_mutex(&table->table_mutex, INIT);
	handle_mutex(&table->print_mutex, INIT);
	
	while (i < table->num_philos)
	{
		table->forks[i].fork_id = i;
		handle_mutex(&table->forks[i].fork, INIT);
		i++;
	}
	init_philo(table);
}

void	init_philo(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->num_philos)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->full_meals = false;
		philo->count_eaten_meals = 0;
		philo->table = table;
		handle_mutex(&philo->philo_mutex, INIT);
		init_forks(philo, table->forks, i);
		i++;
	}
}

// first fork: left, second fork: right
void	init_forks(t_philo *philo, t_fork *fork, int philo_pos)
{
	int num_philos;
	
	num_philos = philo->table->num_philos;
	philo->left_fork = &fork[philo_pos];
	philo->right_fork = &fork[(philo_pos + 1) % num_philos];
	
	// TO AVOID DEADLOCK: odd numbered philosophers pick right fork first
	if (philo->philo_id % 2 == 0)
	{
		philo->left_fork = &fork[(philo_pos + 1) % num_philos];
		philo->right_fork = &fork[philo_pos];
	}
}

void	*handle_malloc(size_t bytes)
{
	void	*ret_value;

	ret_value = malloc(bytes);
	if (ret_value == NULL)
		error_msg("ERROR: malloc failed");
	return (ret_value);
}
