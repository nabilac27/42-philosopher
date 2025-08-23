/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:23:06 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 12:57:58 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool monitor_full(t_table *table)
{
    int i;
    int full_count = 0;

    for (i = 0; i < table->num_philos; i++)
    {
        handle_mutex(&table->philos[i].philo_mutex, LOCK);
        if (table->philos[i].is_full)
            full_count++;
        handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
    }

    if (full_count == table->num_philos)
    {
        table->end_sim = true;
        return true;
    }
    return false;
}


// bool	monitor_died(t_table *table)
// {
// 	unsigned long	time;
// 	int				x;

// 	time = gettime(MILISECOND);
// 	x = 0;
// 	while (x < table->num_philos)
// 	{
// 		handle_mutex(&table->philos[x].philo_mutex, LOCK);
// 		if ((time
// 				- table->philos[x].last_meal_time) >= (unsigned int)table->time_to_die
// 			&& !table->philos[x].is_full)
// 		{
// 			handle_mutex(&table->philos[x].philo_mutex, UNLOCK);
// 			return (true);
// 		}
// 		handle_mutex(&table->philos[x].philo_mutex, UNLOCK);
// 		x++;
// 	}
// 	return (false);
// }

bool monitor_died(t_table *table)
{
    int x;

    x = 0;
    while (x < table->num_philos)
    {
        handle_mutex(&table->philos[x].philo_mutex, LOCK);
        if ((gettime(MILISECOND) - table->philos[x].last_meal_time) >= 
            (unsigned int)table->time_to_die && !table->philos[x].is_full)
        {
            handle_mutex(&table->philos[x].philo_mutex, UNLOCK);
            return (true);
        }
        handle_mutex(&table->philos[x].philo_mutex, UNLOCK);
        x++;
    }
    return (false);
}

bool	philo_died(t_table *table)
{
	int	x;

	x = 0;
	while (x < table->num_philos)
	{
		handle_mutex(&table->philos[x].philo_mutex, LOCK);
		if ((gettime(MILISECOND)
				- table->philos[x].last_meal_time) >= (unsigned int)table->time_to_die
			&& !table->philos[x].is_full)
		{
			log_status(&table->philos[x], "died");
			table->end_sim = true;
			handle_mutex(&table->philos[x].philo_mutex, UNLOCK);
			return (true);
		}
		handle_mutex(&table->philos[x].philo_mutex, UNLOCK);
		x++;
	}
	return (false);
}

// void	*monitor_routine(void *arg)
// {
// 	t_table	*table;
// 	int		i;
// 	long	now;

// 	table = (t_table *)arg;
// 	while (!(table->is_all_threads_ready))
// 		usleep(100);

// 	while (!(table->end_sim))
// 	{
// 		i = 0;
// 		while ((i < table->num_philos) && !(table->end_sim))
// 		{
// 			handle_mutex(&table->philos[i].philo_mutex, LOCK);
// 			now = gettime(MILISECOND);
// 			if (!(table->philos[i].is_full) && (now
// 					- table->philos[i].last_meal_time) >= table->time_to_die)
// 			{
// 				log_status(&table->philos[i], "died");
// 				table->end_sim = true;
// 			}
// 			handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
// 			i++;
// 		}
// 		usleep(500); // small delay to reduce CPU usage
// 	}
// 	return (NULL);
// }

// void *monitor_routine(void *arg)
// {
//     t_table *table = (t_table *)arg;

//     while (!table->is_all_threads_ready)
//         usleep(100);

//     while (!table->end_sim)
//     {
//         if (monitor_died(table))
//             break;
//         if (monitor_full(table))
//             break;
//         usleep(500);
//     }
//     return NULL;
// }

// void *monitor_routine(void *arg)
// {
//     t_table *table = (t_table *)arg;
//     int i;

//     while (!table->end_sim)
//     {
//         i = 0;
//         while (i < table->num_philos && !table->end_sim)
//         {
//             handle_mutex(&table->philos[i].philo_mutex, LOCK);
//             long now = gettime(MILISECOND);
//             if (!table->philos[i].is_full
//                 && (now - table->philos[i].last_meal_time) >= table->time_to_die)
//             {
//                 log_status(&table->philos[i], "died");
//                 table->end_sim = true;
//             }
//             handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
//             i++;
//         }
//         usleep(100); // <- faster loop to catch death
//     }
//     return NULL;
// }

// void *monitor_routine(void *arg)
// {
//     t_table *table = (t_table *)arg;
//     int i;

//     while (!table->is_all_threads_ready)
//         usleep(100);

//     while (!table->end_sim)
//     {
//         // Check for full philosophers (one pass)
//         if (monitor_full(table))
//             break;
            
//         // Check for death (one pass)
//         i = 0;
//         while (i < table->num_philos && !table->end_sim)
//         {
//             handle_mutex(&table->philos[i].philo_mutex, LOCK);
//             unsigned long now = gettime(MILISECOND);
//             // Convert time_to_die from microseconds to milliseconds for comparison
//             if (!table->philos[i].is_full && 
//                 (now - table->philos[i].last_meal_time) >= (table->time_to_die / 1000))
//             {
//                 log_status(&table->philos[i], "died");
//                 table->philo_dead = true;
//                 table->end_sim = true;
//                 handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
//                 break;
//             }
//             handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
//             i++;
//         }
        
//         // More frequent checking for death with fewer philosophers
//         usleep(100); // Check more frequently to detect death accurately
//     }
//     return NULL;
// }

void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;
    int i;

    while (!table->is_all_threads_ready)
        usleep(100);

    while (!table->end_sim)
    {
        // Check for full philosophers (one pass)
        if (monitor_full(table))
            break;
            
        // Check for death (one pass)
        i = 0;
        while (i < table->num_philos && !table->end_sim)
        {
            handle_mutex(&table->philos[i].philo_mutex, LOCK);
            unsigned long now = gettime(MILISECOND);
            
            if (!table->philos[i].is_full && 
				(now - table->philos[i].last_meal_time) >= table->time_to_die)
            {
                log_status(&table->philos[i], "died");
                table->philo_dead = true;
                table->end_sim = true;
                handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
                
                // Print an exit message so the user knows termination is happening
                printf("Philosopher %ld died, ending simulation...\n", table->philos[i].philo_id);
                return NULL;  // Exit immediately
            }
            handle_mutex(&table->philos[i].philo_mutex, UNLOCK);
            i++;
        }
        
        usleep(50);  // Shorter sleep for more responsive detection
    }
    return NULL;
}


void	log_status(t_philo *philo, const char *status)
{
	t_table	*table;
	long	now;

	table = philo->table;
	handle_mutex(&table->print_mutex, LOCK);
	if (!table->end_sim)
	{
		now = gettime(MILISECOND);
		printf("%ld %ld %s\n", now - table->start_sim, philo->philo_id, status);
	}
	handle_mutex(&table->print_mutex, UNLOCK);
}
