/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:37:56 by nchairun          #+#    #+#             */
/*   Updated: 2025/07/25 22:24:25 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table t_table;

typedef struct s_philo
{
	int             id;
	int             num_eaten_meals;
	long long       time_last_meal;
    
	// pthread_t       thread;
	// pthread_mutex_t *left_fork;
	// pthread_mutex_t *right_fork;
    
	t_table         *table;
}	t_philo;

typedef struct s_table
{
	int             num_philos;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             num_must_meals;
	int             death_philo;
	long long       start_time;

	// pthread_mutex_t print_mutex;
	// pthread_mutex_t death_mutex;
	// pthread_mutex_t meal_check_mutex;
	// pthread_mutex_t *forks;

	t_philo         *philos;
}	t_table;


// utils.c
bool	    check_valid_args(int argc, char *argv[]);
int	        ft_atoi(char *str);

#endif
