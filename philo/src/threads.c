/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 15:19:00 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/02 13:55:44 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*thread_monitor(void *table);
void	*thread_routine(void *table);
bool	meal_round_finished(t_table *table);
bool	philo_died(t_table *table);

bool	setup_thread(t_table *table)
{
	pthread_t	monitor_thread;
	int			i;

	// monitor thread
	if (pthread_create(&monitor_thread, NULL, &thread_monitor, table) != 0)
		return (false);

	// philosopher threads
	i = 0;
	while (i < (table->num_philos))
	{
		if (pthread_create(&table->philos[i].thread, NULL, &thread_routine, &table->philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(table->philos[i].thread, NULL);
			pthread_join(monitor_thread, NULL);
			return (false);
		}
		i++;
	}

	// Wait for monitor thread to finish
	if (pthread_join(monitor_thread, NULL) != 0)
		return (false);
	
	// Join philosopher threads
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (true);
}

void	*thread_monitor(void *table)
{
   t_table *p_table = (t_table *)table;
	
	while (p_table != NULL)
	{
		if (meal_round_finished(p_table) || philo_died(p_table))
			break ;
	}
	printf("thread_monitor\n");
	return(p_table);
}

void	*thread_routine(void *philo)
{
	t_philo *p_philo = (t_philo *)philo;
	printf("Philosopher %d is thinking...\n", p_philo->id);
	usleep(1000 * 500);  // 500 ms
	printf("Philosopher %d is done.\n", p_philo->id);
	return NULL;
}

bool	meal_round_finished(t_table *table)
{
	int	i;
	int	philos_finished_eating;

	if (table->num_must_meals == -1)
		return (false);

	pthread_mutex_lock(&table->meal_mutex);
	philos_finished_eating = 0;
	i = 0;
	while (i < table->num_philos)
	{
		if (table->philos[i].num_eaten_meals >= table->num_must_meals)
			philos_finished_eating++;
		i++;
	}
	pthread_mutex_unlock(&table->meal_mutex);

	return (philos_finished_eating == table->num_philos);
}

bool	philo_died(t_table *table)
{
	int			i;
	long long	current_time;
	struct timeval	time;

	pthread_mutex_lock(&table->death_mutex);
	if (table->death_philo != 0)
	{
		pthread_mutex_unlock(&table->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->death_mutex);

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);

	pthread_mutex_lock(&table->meal_mutex);
	i = 0;
	while (i < table->num_philos)
	{
		if (current_time - table->philos[i].last_meal_time > table->time_to_die)
		{
			pthread_mutex_unlock(&table->meal_mutex);
			pthread_mutex_lock(&table->death_mutex);
			table->death_philo = table->philos[i].id;
			pthread_mutex_unlock(&table->death_mutex);
			return (true);
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal_mutex);
	return (false);
}
