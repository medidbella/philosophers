/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:48 by midbella          #+#    #+#             */
/*   Updated: 2024/04/25 21:46:10 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_data(t_data *ref, char **av)
{
	ref->philo_number = ft_atoi(av[1]);
	ref->life_time = ft_atoi(av[2]);
	ref->eat_time = ft_atoi(av[3]);
	ref->sleep_time = ft_atoi(av[4]);
	ref->forks = ref->philo_number;
	if (av[5])
		ref->max_eat_time = ft_atoi(av[5]);
	else
		ref->max_eat_time = -1;
}

int	main(int ac, char **av)
{
	t_data	prog_data;

	if (!check_args(ac, av))
		return (1);
	initialize_data(&prog_data, av);
}
