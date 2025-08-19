/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:37:56 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/19 22:45:07 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_fork	t_fork;
typedef struct s_table	t_table;
typedef struct s_philo
{
	long				philo_id;
	bool				full_meals;
	long				count_eaten_meals;
	long				last_meal_time;

	t_table				*table;

	t_fork				*left_fork;
	t_fork				*right_fork;

	pthread_t			thread_id;
}						t_philo;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_table
{
	long				num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_must_meals;

	long				start_sim;
	bool				end_sim;
	bool 				threads_ready; // synchro philos

	t_fork				*forks;
	t_philo				*philos;

	t_mutex table_mutex; // TO AVOID RACES WHILE READING FROM TABLE
}						t_table;

typedef enum e_mutex_type
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
}						t_mutex_type;

typedef enum e_thread_type
{
	CREATE,
}						t_thread_type;

// main.c
void					error_msg(char *msg);

// parse_table.c
void					parse_table(t_table *table, char **argv);
bool					check_valid_args(int argc, char *argv[]);
long					ft_atol(char *str);

// init_table.c
void					init_data(t_table *table);
void					init_philo(t_table *table);
void					init_forks(t_philo *philo, t_fork *fork, int philo_pos);

// handle_mutex.c
void					*handle_malloc(size_t bytes);
void					handle_mutex(t_mutex *fork, t_mutex_type type);

// exec_dinner.c
void	exec_dinner(t_table *table);
void	*dinner_sim(void *data);

// setter_getter.c
void	set_bool(t_mutex *fork, bool *dest, bool value);
bool	get_bool(t_mutex *fork, bool value);
long	get_long(t_mutex *fork, long *value);
void	set_long(t_mutex *fork, long *dest, long value);
bool	sim_finished(t_table *table);

// synchro_philos.c
void    wait_all_threads(t_table *table);

#endif
