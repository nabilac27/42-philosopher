/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:37:56 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 09:11:16 by nchairun         ###   ########.fr       */
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
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

/* ############################################################
			STRUCT	--	t_table,  t_philo,  t_fork
############################################################ */

typedef struct s_table
{
	long				num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_must_meals;
	long				start_sim;
	bool				end_sim;
	bool				is_all_threads_ready;
	long				num_threads_ready;
	long				num_threads_running;
	t_fork				*forks;
	t_philo				*philos;
	t_mutex				table_mutex;
	t_mutex				print_mutex;
	pthread_t			monitor;
}						t_table;

typedef struct s_philo
{
	long				philo_id;
	long				count_eaten_meals;
	long				last_meal_time;
	bool				is_full;
	t_table				*table;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_mutex				philo_mutex;
}						t_philo;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

/* ######################################################################
   ENUM --	t_mutex_type,  t_thread_type,  t_time_type, t_philo_status
###################################################################### */

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
	JOIN,
	DETACH,
}						t_thread_type;

typedef enum e_time_type
{
	SECOND,
	MILISECOND,
	MICROSECOND,
}						t_time_type;

typedef enum e_philo_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DEAD,
}						t_philo_status;

/* ############################################################
						src/01-parse
############################################################ */

// parse_table.c
void					parse(t_table *table, int argc, char **argv);

// clean_table.c
void					clean(t_table *table);
void					error_msg(char *msg);

/* ############################################################
						src/02-init_table
############################################################ */

// init_table_struct.c

void					init_philo_struct(t_table *table);
void					init_table_struct(t_table *table);

// handle_mutex.c
void					*handle_malloc(size_t bytes);
void					handle_mutex(t_mutex *fork, t_mutex_type type);

/* ############################################################
						src/03-threads
############################################################ */

// threads.c
void					init_philo_threads(t_table *table);
void					init_monitor_thread(t_table *table);
void					wait_all_philo_threads_finish(t_table *table);
void					wait_monitor_thread_finish(t_table *table);

/* ############################################################
						src/04-routines
############################################################ */

// philo_routine.c
void					*philo_routine(void *arg);

// monitor_routine.c
void					log_status(t_philo *philo, const char *status);
void					*monitor_routine(void *arg);

// utils.c
void					initial_delay(t_philo *philo);
void					delay_time(long usec, t_table *table);
long					get_time_ms(void);
void					precise_sleep(long duration_us);
long					get_elapsed_time(t_table *table);

#endif
