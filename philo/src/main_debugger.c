#include "../include/philo.h"

/*
    Your program(s) must take the following arguments:
        1. number_of_philosophers  
        2. time_to_die 
        3. time_to_eat 
        4. time_to_sleep 
        5. number_of_times_each_philosopher_must_eat
*/

int main(int argc, char *argv[])
{
    t_table *table;
    
    if (!(argc == 5 || argc == 6) || !(check_valid_args(argc, argv))) 
        return(1);

    table = setup_table(argc, argv);
    if (!(table))
		return(1);
    printf("✅ Table Initialized\n");
    printf("Number of Philosophers: %d\n", table->num_philos);
    printf("Time to die: %d\n", table->time_to_die);
    printf("Time to eat: %d\n", table->time_to_eat);
    printf("Time to sleep: %d\n", table->time_to_sleep);
    printf("Number of meals required: %d\n", table->num_must_meals);

    for (int i = 0; i < table->num_philos; i++)
    {
        printf("Philosopher %d initialized. Last meal time: %lld\n",
            table->philos[i].id, table->philos[i].last_meal_time);
    }

    printf("\n🚀 Launching threads...\n");

    if (!setup_thread(table))
    {
        fprintf(stderr, "❌ Failed to launch threads\n");
        return (1);
    }

    printf("✅ All threads finished successfully\n");

    free(table->philos);
    free(table->forks);
    free(table);
    return (0);
}