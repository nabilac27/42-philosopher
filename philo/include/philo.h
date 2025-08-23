/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:37:56 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 15:17:49 by nchairun         ###   ########.fr       */
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
# include <sys/time.h>
# include <unistd.h>

/* ############################################################
   TYPEDEFS
############################################################ */

typedef pthread_mutex_t	t_mutex;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

/* ############################################################
   STRUCTS
############################################################ */

typedef struct s_table
{
	long				num_philos;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	long				time_to_sleep;
	long				num_must_meals;
	long				start_sim;
	bool				end_sim;
	bool				is_all_threads_ready;
	long				num_threads_ready;
	volatile bool		philo_dead;

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
	t_mutex				fork;
	int					fork_id;
}						t_fork;

/* ############################################################
   ENUMS
############################################################ */

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
	MILISECOND,
	MICROSECOND
}						t_time_type;

/* ############################################################
   PROTOTYPES
############################################################ */

/* src/01-parse */
void					parse(t_table *table, int argc, char **argv);
void					clean(t_table *table);
void					error_msg(char *msg);

/* src/02-init_table */
void					init_philo_struct(t_table *table);
void					init_table_struct(t_table *table);
void					*handle_malloc(size_t bytes);
void					handle_mutex(t_mutex *mutex, t_mutex_type type);

/* src/03-threads */
void					init_philo_threads(t_table *table);
void					init_monitor_thread(t_table *table);
void					wait_all_philo_threads_finish(t_table *table);
void					wait_monitor_thread_finish(t_table *table);

/* src/04-routines */
/* monitor_routine */
void					*monitor_routine(void *arg);
void					log_status(t_philo *philo, const char *status);

/* philo_routine */
void					*philo_routine(void *arg);

/* philo_routine_utils */
void					eat(t_philo *philo);
void					sleep_philo(t_philo *philo);
void					think(t_philo *philo);

/* time_utils */
void					initial_delay(t_philo *philo);
void					delay_time(long usec, t_table *table);
long					gettime(t_time_type type);
void					precise_sleep(long duration_ms, t_table *table);

#endif
