/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functoins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:04:54 by midbella          #+#    #+#             */
/*   Updated: 2024/05/27 19:05:51 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
}

unsigned long	ft_get_time(void)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec * 1000) + (curr.tv_usec / 1000));
}

void	ft_sleep(unsigned long time)
{
	unsigned long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		ft_sleep(1);
	return ;
}

int	check_args(int ac, char **av)
{
	int	s_index;
	int	c_index;

	s_index = 1;
	c_index = 0;
	if (ac < 5 || ac > 6)
		return (0);
	while (av[s_index])
	{
		c_index = 0;
		while (av[s_index][c_index])
		{
			if (!(av[s_index][c_index] >= '0' && av[s_index][c_index] <= '9'))
				return (0);
			c_index++;
		}
		s_index++;
	}
	return (1);
}
