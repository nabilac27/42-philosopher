/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchairun <nchairun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:01:19 by nchairun          #+#    #+#             */
/*   Updated: 2025/07/25 21:41:21 by nchairun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
	TO-DO:
	* check_valid_args for INT_MIN, INT_MAX numbers
	* using long
*/

bool	check_valid_args(int argc, char *argv[])
{
	int			i;
	int			j;
	long long	value;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '+' || argv[i][j] == '-')
			j++;
		if (argv[i][j] == '\0')
			return(false);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return(false);
			j++;
		}
		value = ft_atol(argv[i]);
		if (value > INT_MAX || value < INT_MIN)
			return(false);

		i++;
	}
	return(true);
}

long long	ft_atol(char *str)
{
	long long	result;
	int			sign;
	int			i;
	
	result = 0;
	sign = 1;
	i = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
