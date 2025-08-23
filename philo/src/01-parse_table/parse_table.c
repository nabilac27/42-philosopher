/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:57:17 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 03:26:58 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"


void	parse_table(t_table *table, char **argv)
{
	table->num_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if(table->num_philos < 1)
		error_msg("ERROR: Philos must be more than 0");
	if (table->num_philos < 1 || table->time_to_die < 1 || table->time_to_eat < 1
			|| table->time_to_sleep < 1)
		error_msg("ERROR: parse_table()");
	if (argv[5])
	{
		table->num_must_meals = ft_atol(argv[5]);
		if (table->num_must_meals < 1)
			error_msg("ERROR: parse_table()");
	}
	else
		table->num_must_meals = -1;
}

bool	check_valid_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!(ft_atol(argv[i])))
			return (false);
		i++;
	}
	return (true);
}

long	ft_atol(char *str)
{
	int			i;
	int			negative;
	long long	result;

	i = 0;
	negative = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			error_msg("ERROR: Only positive numbers allowed");
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			error_msg("ERROR: Only 0-9 allowed");
		result = (str[i] - '0') + (result * 10);
		i++;
	}
	if (result < INT_MIN || result > INT_MAX)
		return (0);
	return ((int)result * negative);
}

void	error_msg(char *msg)
{
	printf("%s \n", msg);
	exit(1);
}

void    clean(t_table   *table)
{
    t_philo *philo;
    int     i;

    i = 0;
    while (i++ < table->num_philos)
    {
        philo = table->philos + i;
        handle_mutex(&philo->philo_mutex, DESTROY);
    }
    handle_mutex(&table->print_mutex, DESTROY);
    handle_mutex(&table->table_mutex, DESTROY);
    free(table->forks);
    free(table->philos);
}