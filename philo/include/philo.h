/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:37:56 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/19 19:32:47 by nchairun         ###   ########.fr       */
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

typedef pthread_mutex_t t_mutex;
typedef struct s_fork t_fork;
typedef struct s_table	t_table;

typedef struct s_philo
{
	long		philo_id;
	// long		num_req_meals;
	long		count_eaten_meals;
	bool		full;
	long 		last_meal_time;
	
	t_fork		*left_fork;
	t_fork		*right_fork;
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
	long			num_must_meals;
	
	long			start_sim;
	bool			end_sim;

	t_fork			*forks;
	t_philo			*philos;
	
	// pthread_mutex_t	*forks;         // Array of fork mutexes
    // pthread_mutex_t	print_mutex;    // Mutex for printing
    // pthread_mutex_t	death_mutex;    // Mutex for death state
    // pthread_mutex_t	meal_mutex;     // Mutex for meal checks
}	t_table;

// main.c
void	error_msg(char *msg);

// parse_table.c
void    parse_table(t_table *table, char **argv);
bool	check_valid_args(int argc, char *argv[]);
long	ft_atol(char *str);


// // utils.c
// bool	    check_valid_args(int argc, char *argv[]);
// int	        ft_atoi(char *str);

// // setup_structs.c
// t_table	*setup_table(int argc, char **argv);
// bool	setup_philo(t_table *table);
// int 	setup_mutex(t_table *table);
// long	gettimeofday_in_ms(void);

// // threads.c
// bool	setup_thread(t_table *table);

#endif
