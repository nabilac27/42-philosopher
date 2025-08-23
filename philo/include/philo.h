/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:37:56 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 07:52:45 by nchairun         ###   ########.fr       */
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
##			STRUCT	--	t_table,  t_philo,  t_fork  			 ##
############################################################ */

typedef struct s_table
{
	long				num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_must_meals;
	long				start_sim;
	bool				is_routine_finished;
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
## ENUM --	t_mutex_type,  t_thread_type,  t_time_type, t_philo_status ##
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
##						src/01-parse							##
############################################################ */

// parse_table.c
void					parse(t_table *table, int argc, char **argv);

// clean_table.c
void					clean(t_table *table);
void					error_msg(char *msg);

/* ############################################################
##						src/02-init_table					 ##
############################################################ */

// init_table_struct.c

void					init_philo_struct(t_table *table);
void					init_table_struct(t_table *table);

// handle_mutex.c
void					*handle_malloc(size_t bytes);
void					handle_mutex(t_mutex *fork, t_mutex_type type);

/* ############################################################
##						src/03-dinner							##
############################################################ */

// dinner.c
void					dinner(t_table *table);
void					*routine_sim(void *data);

// dinner_utils.c
void					eat(t_philo *philo);
void					think(t_philo *philo, bool is_initial);
void					sleeps(t_philo *philo);
void					*philo_1(void *arg);
void					print_status(t_philo *philo, t_philo_status status);

// dinner_monitor.c
void					*dinner_monitor(void *data);
bool					sim_finished(t_table *table);
bool					is_dead_philo(t_philo *philo);

// handle_times.c
void					initial_delay(t_philo *philo);
void					delay_time(long usec, t_table *table);
void					usleep_micro(long time_to_sleep);
long					gettime(t_time_type type);

/* ############################################################
##							src/04-threads						 ##
############################################################ */

// handle_thread.c
void					handle_thread(pthread_t *thread, void *(*foo)(void *),
							void *data, t_thread_type *type);
void					handle_thread_status(int status, t_thread_type *type);
void					wait_all_threads(t_table *table);
bool					is_all_threads_running(t_mutex *fork, long num_philos,
							long *threads);

// handle_thread_utils.c
void					set_bool(t_mutex *fork, bool *dest, bool value);
bool					get_bool(t_mutex *fork, bool *value);
long					get_long(t_mutex *fork, long *value);
void					set_long(t_mutex *fork, long *dest, long value);
bool					sim_finished(t_table *table);

#endif
