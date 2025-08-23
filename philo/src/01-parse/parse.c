/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:57:17 by nchairun          #+#    #+#             */
/*   Updated: 2025/08/23 09:38:23 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

bool	is_positive(const char *str)
{
	int	i;

	i = 0;
	if ((str == NULL) || (str[0] == '\0'))
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	check_positive(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!(is_positive(argv[i])))
			return (false);
		i++;
	}
	return (true);
}

long	ft_atol(const char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		if (res > LONG_MAX)
			return (-1);
		i++;
	}
	return (res);
}

void	parse(t_table *table, int argc, char **argv)
{
	if (!(check_positive(argc, argv)))
		error_msg("ERROR: parse() -- All arguments must be positive\n");
	table->num_philos = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
	{
		table->num_must_meals = ft_atol(argv[5]);
		if (table->num_must_meals < 1)
			error_msg("ERROR: parse_table() -- invalid num_must_meals");
	}
	else
		table->num_must_meals = -1;
	if (table->num_philos < 1 || table->time_to_die < 1
		|| table->time_to_eat < 1 || table->time_to_sleep < 1)
		error_msg("ERROR: parse() -- Number of philos and times");
}
