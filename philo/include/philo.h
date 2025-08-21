/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:37:56 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/21 15:26:46 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <errno.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

/* ############################################################
##			STRUCT	--	t_table,  t_philo,  t_fork		  	 ##
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
	bool 				threads_ready; // synchro philos
	long				num_threads_ready;
	
	t_fork				*forks;
	t_philo				*philos;

	t_mutex table_mutex; // TO AVOID RACES WHILE READING FROM TABLE
	t_mutex	print_mutex;
}						t_table;

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
}	t_time_type;

typedef enum e_philo_status
{
	EAT,
	SLEEP,
	THINK,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DEAD,
}	t_philo_status;


/* ############################################################
##				    	01-parse_table			  			 ##
############################################################ */

// parse_table.c
void					parse_table(t_table *table, char **argv);
bool					check_valid_args(int argc, char *argv[]);
long					ft_atol(char *str);

// clean_table.c
void					error_msg(char *msg);

/* ############################################################
##						02-init_table		  				 ##
############################################################ */

// init_table.c
void					init_table(t_table *table);
void					init_philo(t_table *table);
void					init_forks(t_philo *philo, t_fork *fork, int philo_pos);
void					*handle_malloc(size_t bytes);

// handle_mutex.c
void					handle_mutex(t_mutex *fork, t_mutex_type type);
void					handle_mutex_status(int status, t_mutex_type type);

/* ############################################################
##						03-dinner							 ##
############################################################ */

// dinner.c
void	dinner(t_table *table);
void 	*dinner_monitor(void *data);

// dinner_utils.c
void	usleep_micro(long time_to_sleep_us);
void    wait_all_threads(t_table *table);
long 	gettime(t_time_type type);

// handle_thread.c
void 	handle_thread(pthread_t *thread, void *(*foo)(void *), void *data, t_thread_type *type);
void 	handle_thread_status(int status, t_thread_type  *type);

// handle_thread_utils.c
void	set_bool(t_mutex *fork, bool *dest, bool value);
bool	get_bool(t_mutex *fork, bool *value);
long	get_long(t_mutex *fork, long *value);
void	set_long(t_mutex *fork, long *dest, long value);
bool	sim_finished(t_table *table);

// routine.c
void	*routine_sim(void *data);
void 	eat(t_philo *philo);
// void 	sleep(t_philo *philo); 
void 	think(t_philo *philo);
void    print_status(t_philo *philo, t_philo_status status);

#endif
