/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 22:28:30 by nchairun          #+#    #+#             */
/*   Updated: 2025/07/30 13:32:21 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/* TO-DO:
	- improve setup mutex and philo
	- Thread routine(eat, sleep, think loop)
    - destroy_mutex
    _ Thread monitor 
 */

bool	setup_philo(t_table *table);
int 	setup_mutex(t_table *table);

t_table	*setup_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);

	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->num_must_meals = -1;
	if (argc == 6)
		table->num_must_meals = ft_atoi(argv[5]);
	if (!(setup_philo(table)) || !(table->philos))
		return (free(table), NULL);
	if (!(setup_mutex(table)))
		return (free(table->philos), free(table), NULL);
	return (table);
}

bool setup_philo(t_table *table)
{
    int i;
	struct timeval	time;

    table->philos = malloc(sizeof(t_philo) * table->num_philos);
    if (!(table->philos))
        return false;
    memset(table->philos, 0, sizeof(t_philo) * table->num_philos);
    i = 0;
    while (i < table->num_philos)
    {
        table->philos[i].id = i + 1;
        table->philos[i].start_meal_time = 0;
        table->philos[i].last_meal_time = gettimeofday(&time, NULL);;
        table->philos[i].table = table;
        i++;
    }
    return true;
}

// setup_mutex*
int setup_mutex(t_table *table)
{
    int i;

    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
    if (!table->forks)
        return 0;

    i = 0;
    while (i < table->num_philos)
    {
        if (pthread_mutex_init(&table->forks[i], NULL) != 0)
        {
            perror("Mutex init failed");
            // Cleanup already initialized mutexes before returning
            while (--i >= 0)
                pthread_mutex_destroy(&table->forks[i]);
            free(table->forks);
            return 0;
        }
        i++;
    }

    if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
    {
        perror("Print mutex init failed");
        i = 0;
        while (i < table->num_philos)
        {
            pthread_mutex_destroy(&table->forks[i]);
            i++;
        }
        free(table->forks);
        return 0;
    }

    if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
    {
        perror("Death mutex init failed");
        pthread_mutex_destroy(&table->print_mutex);
        i = 0;
        while (i < table->num_philos)
        {
            pthread_mutex_destroy(&table->forks[i]);
            i++;
        }
        free(table->forks);
        return 0;
    }

    if (pthread_mutex_init(&table->meal_mutex, NULL) != 0)
    {
        perror("Meal mutex init failed");
        pthread_mutex_destroy(&table->death_mutex);
        pthread_mutex_destroy(&table->print_mutex);
        i = 0;
        while (i < table->num_philos)
        {
            pthread_mutex_destroy(&table->forks[i]);
            i++;
        }
        free(table->forks);
        return 0;
    }

    return 1; 
}

// t_table	*setup_table(int argc, char **argv)
// {
// 	t_table	*table;

// 	table = malloc(sizeof(t_table));
// 	if (!(table))
// 		return (NULL);
        
// 	table->num_philos = ft_atoi(argv[1]);
// 	table->time_to_die = ft_atoi(argv[2]);
// 	table->time_to_eat = ft_atoi(argv[3]);
// 	table->time_to_sleep = ft_atoi(argv[4]);
    
// 	table->num_must_meals = -1;
//     if (argc == 6)
// 		table->num_must_meals = ft_atoi(argv[5]);
//     setup_philo(table);
// 	if (table->philos == NULL)
// 		return (free(table), table = NULL, NULL);
// 	setup_mutex(table);
// 	return (table);
// }

// void	setup_philo(t_table *table)
// {
// 	int	i;

// 	table->philos = malloc(sizeof(t_philo) * (table->num_philos));
// 	if (!(table->philos))
// 		return ;
// 	memset(table->philos, 0, (sizeof(t_philo) * table->num_philos));
// 	i = 0;
// 	while (i < (table->num_philos))
// 	{
// 		table->philos[i].id = i + 1;
// 		table->philos[i].start_meal_time = 0;
// 		table->philos[i].last_meal_time = get_time();
// 		table->philos[i].table = table;
// 		i++;
// 	}
// }
