/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:20:04 by midbella          #+#    #+#             */
/*   Updated: 2024/05/17 18:34:24 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int s_index;
	int c_index;

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