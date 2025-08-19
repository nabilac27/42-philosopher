/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:37:56 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/19 17:53:11 by nchairun         ###   ########.fr       */
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
# include <string.h>

typedef struct s_table	t_table;

// typedef struct p_thread_mutex_t
// {
// 	p_thread_mutex_t;
// }
// 	t_mutex;

typedef struct s_philo
{
	int			id;
	int			num_req_meals;
	int			num_eaten_meals;
	bool		full;
	
	// long long	start_meal_time;
	long long	last_meal_time;

	pthread_t	thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;

	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

typedef struct s_fork 
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_table
{
	long			num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	
	long			num_max_meals;
	// int			death_philo;
	long long		start_sim;
	bool			end_sim;

	t_fork			*fork;
	t_philo			*philo;
	
	// pthread_mutex_t	*forks;         // Array of fork mutexes
    // pthread_mutex_t	print_mutex;    // Mutex for printing
    // pthread_mutex_t	death_mutex;    // Mutex for death state
    // pthread_mutex_t	meal_mutex;     // Mutex for meal checks
	t_philo         *philos;
}	t_table;


// utils.c
bool	    check_valid_args(int argc, char *argv[]);
int	        ft_atoi(char *str);

// setup_structs.c
t_table	*setup_table(int argc, char **argv);
bool	setup_philo(t_table *table);
int 	setup_mutex(t_table *table);
long	gettimeofday_in_ms(void);

// threads.c
bool	setup_thread(t_table *table);

#endif
