/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 08:13:11 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 13:15:52 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// static void	take_forks(t_philo *philo)
// {
// 	if (philo->philo_id % 2 == 0)
// 	{
// 		handle_mutex(&philo->right_fork->fork, LOCK);
// 		log_status(philo, "has taken a fork");
// 		handle_mutex(&philo->left_fork->fork, LOCK);
// 		log_status(philo, "has taken a fork");
// 	}
// 	else
// 	{
// 		handle_mutex(&philo->left_fork->fork, LOCK);
// 		log_status(philo, "has taken a fork");
// 		handle_mutex(&philo->right_fork->fork, LOCK);
// 		log_status(philo, "has taken a fork");
// 	}
// }

// static void take_forks(t_philo *philo)
// {
//     t_table *table = philo->table;
    
//     // Check if simulation has ended
//     if (table->end_sim)
//         return;
    
//     // Use even/odd strategy to prevent deadlocks, but with timeout
//     if (philo->philo_id % 2 == 0)
//     {
//         // Even philosophers take right fork first
//         handle_mutex(&philo->right_fork->fork, LOCK);
//         log_status(philo, "has taken a fork");
        
//         // Give up first fork if can't acquire second within reasonable time
//         unsigned long start_wait = gettime(MILISECOND);
//         while (pthread_mutex_lock(&philo->left_fork->fork) != 0)
//         {
//             if (table->end_sim || 
//                 (gettime(MILISECOND) - start_wait) > (table->time_to_die / 4))
//             {
//                 // Release the first fork and retry later
//                 handle_mutex(&philo->right_fork->fork, UNLOCK);
//                 usleep(philo->philo_id * 1000); // Back off proportionally
//                 return take_forks(philo); // Recursive retry
//             }
//             usleep(50);
//         }
//         log_status(philo, "has taken a fork");
//     }
//     else
//     {
//         // Odd philosophers take left fork first
//         handle_mutex(&philo->left_fork->fork, LOCK);
//         log_status(philo, "has taken a fork");
        
//         // Similar timeout strategy for second fork
//         unsigned long start_wait = gettime(MILISECOND);
//         while (pthread_mutex_lock(&philo->right_fork->fork) != 0)
//         {
//             if (table->end_sim || 
//                 (gettime(MILISECOND) - start_wait) > (table->time_to_die / 4))
//             {
//                 handle_mutex(&philo->left_fork->fork, UNLOCK);
//                 usleep(philo->philo_id * 1000);
//                 return take_forks(philo);
//             }
//             usleep(50);
//         }
//         log_status(philo, "has taken a fork");
//     }
// }

static void take_forks(t_philo *philo)
{
    t_table *table = philo->table;
    
    // Check if simulation has ended
    if (table->end_sim)
        return;
    
    // Calculate hunger level (how close to death)
    unsigned long now = gettime(MILISECOND);
    unsigned long hunger = now - philo->last_meal_time;
    bool is_critical = hunger >= (table->time_to_die * 3 / 4);
    
    // For very hungry philosophers, do an immediate attempt
    if (is_critical)
    {
        // Skip the delay completely for starving philosophers
    }
    else if (philo->philo_id % 2 == 0)
    {
        // Longer delay for even philosophers when not critical
        usleep(table->time_to_eat / 4);
    }
    else
    {
        // Short delay for odd philosophers when not critical
        usleep(50);
    }
    
    // Use even/odd strategy to prevent deadlocks
    if (philo->philo_id % 2 == 0)
    {
        handle_mutex(&philo->right_fork->fork, LOCK);
        log_status(philo, "has taken a fork");
        handle_mutex(&philo->left_fork->fork, LOCK);
        log_status(philo, "has taken a fork");
    }
    else
    {
        handle_mutex(&philo->left_fork->fork, LOCK);
        log_status(philo, "has taken a fork");
        handle_mutex(&philo->right_fork->fork, LOCK);
        log_status(philo, "has taken a fork");
    }
}

static void	release_forks(t_philo *philo)
{
	handle_mutex(&philo->left_fork->fork, UNLOCK);
	handle_mutex(&philo->right_fork->fork, UNLOCK);
}

// void	eat(t_philo *philo)
// {
// 	t_table	*table;

// 	table = philo->table;
// 	take_forks(philo);
// 	handle_mutex(&philo->philo_mutex, LOCK);
// 	philo->last_meal_time = gettime(MILISECOND);
// 	philo->count_eaten_meals++;
// 	if (table->num_must_meals > 0
// 		&& philo->count_eaten_meals >= table->num_must_meals)
// 		philo->is_full = true;
// 	handle_mutex(&philo->philo_mutex, UNLOCK);
// 	log_status(philo, "is eating");
// 	precise_sleep(table->time_to_eat);
// 	release_forks(philo);
// }

void eat(t_philo *philo)
{
    t_table *table;

    table = philo->table;
    
    // Check if simulation has ended before taking forks
    if (table->end_sim)
        return;
        
    take_forks(philo);
    
    // Check again after taking forks
    if (table->end_sim)
    {
        release_forks(philo);
        return;
    }
    
    handle_mutex(&philo->philo_mutex, LOCK);
    philo->last_meal_time = gettime(MILISECOND);
    philo->count_eaten_meals++;
    if (table->num_must_meals > 0
        && philo->count_eaten_meals >= table->num_must_meals)
        philo->is_full = true;
    handle_mutex(&philo->philo_mutex, UNLOCK);
    
    log_status(philo, "is eating");
    precise_sleep(table->time_to_eat, table);  // Pass table to check end_sim
    release_forks(philo);
}

void sleep_philo(t_philo *philo)
{
    if (philo->table->end_sim)
        return;
        
    log_status(philo, "is sleeping");
    precise_sleep(philo->table->time_to_sleep, philo->table);    
}

// void	sleep_philo(t_philo *philo)
// {
// 	log_status(philo, "is sleeping");
// 	precise_sleep(philo->table->time_to_sleep);
// }

void think(t_philo *philo)
{
    t_table *table = philo->table;
    
    log_status(philo, "is thinking");
    
    // Calculate how long we can safely think
    unsigned long now = gettime(MILISECOND);
    unsigned long time_since_last_meal = now - philo->last_meal_time;
    unsigned long safe_think_time = 0;
    
    // Only wait if we have time to spare before getting hungry
    if (table->time_to_die > time_since_last_meal + 50)
    {
        // Calculate safe thinking time to avoid death
        safe_think_time = (table->time_to_die - time_since_last_meal) / 2;
        
        // Cap thinking time to a reasonable value
        if (safe_think_time > table->time_to_eat / 2)
            safe_think_time = table->time_to_eat / 2;
            
        // Very short minimum think time to allow some concurrency
        if (safe_think_time < 20)
            safe_think_time = 20;
            
        // Think for the calculated safe time
        usleep(safe_think_time * 1000);
    }
}

static void	wait_for_all_threads_ready(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	handle_mutex(&table->table_mutex, LOCK);
	philo->last_meal_time = gettime(MILISECOND);
	table->num_threads_ready++;
	if (table->num_threads_ready == table->num_philos)
	{
		table->is_all_threads_ready = true;
		table->start_sim = gettime(MILISECOND);
	}
	handle_mutex(&table->table_mutex, UNLOCK);
	while (!(table->is_all_threads_ready))
		usleep(100);
}

static void	run_single_philosopher(t_philo *philo)
{
	handle_mutex(&philo->left_fork->fork, LOCK);
	log_status(philo, "has taken a fork");
	precise_sleep(philo->table->time_to_die, philo->table);
	handle_mutex(&philo->left_fork->fork, UNLOCK);
}

// void *philo_routine(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;
//     t_table *table = philo->table;

//     wait_for_all_threads_ready(philo);
//     if (table->num_philos == 1)
//     {
//         run_single_philosopher(philo);
//         return (NULL);
//     }
    
//     // Better staggering - scale delay with philosopher count
//     if (philo->philo_id % 2 == 0)
//         usleep(philo->table->time_to_eat / 2);
    
//     while (!table->end_sim && !philo->is_full)
//     {
//         eat(philo);
//         if (table->end_sim || philo->is_full)
//             break;
//         sleep_philo(philo);
//         if (table->end_sim || philo->is_full)
//             break;
//         think(philo);
//     }
//     return (NULL);
// }

// void *philo_routine(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;
//     t_table *table = philo->table;

//     wait_for_all_threads_ready(philo);
//     if (table->num_philos == 1)
//     {
//         run_single_philosopher(philo);
//         return (NULL);
//     }
    
//     // Create a staggered start based on philosopher ID
//     // This prevents all philosophers from trying to eat at the same time
//     usleep(50 * philo->philo_id);
    
//     while (!table->end_sim && !philo->is_full)
//     {
//         eat(philo);
//         if (table->end_sim || philo->is_full)
//             break;
//         sleep_philo(philo);
//         if (table->end_sim || philo->is_full)
//             break;
//         think(philo);
//     }
//     return (NULL);
// }

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_table *table = philo->table;

    wait_for_all_threads_ready(philo);
    if (table->num_philos == 1)
    {
        run_single_philosopher(philo);
        return (NULL);
    }
    
    // Better staggering strategy
    if (philo->philo_id % 2 == 0)
    {
        // Have even philosophers wait a bit longer
        usleep(5000); // 5ms delay
    }
    
    while (!table->end_sim && !philo->is_full)
    {
        eat(philo);
        if (table->end_sim || philo->is_full)
            break;
        sleep_philo(philo);
        if (table->end_sim || philo->is_full)
            break;
        think(philo);
    }
    return (NULL);
}