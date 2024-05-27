/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:48 by midbella          #+#    #+#             */
/*   Updated: 2024/05/27 20:53:36 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	repititve_meal(t_philo *ref)
{
	pthread_mutex_lock(ref->l_fork);
	print_message("%lu\t%d has taken a fork\n", ref->data, ref->philo_number);
	pthread_mutex_lock(ref->r_fork);
	print_message("%lu\t%d has taken a fork\n", ref->data, ref->philo_number);
	print_message("%lu\t%d is eating\n", ref->data, ref->philo_number);
	ref->last_meal_time = ft_get_time();
	ref->meals_number += 1;
	ft_sleep(ref->data->eat_time);
	printf("clear\n");
	pthread_mutex_unlock(ref->r_fork);
	pthread_mutex_unlock(ref->l_fork);
	return ;
}

void	thread_function(t_philo *ref)
{
	if (ref->philo_number % 2 == 0)
		ft_sleep(40);
	while (1)
	{
		print_message("%lu\t%d is thinking\n", ref->data, ref->philo_number);
		repititve_meal(ref);
		print_message("%lu\t%d is sleeping\n", ref->data, ref->philo_number);
		ft_sleep(ref->data->sleep_time);
	}
	return ;
}

void	monitoring(t_data *ref)
{
	int	i;

	i = 0;
	while (1)
	{
		if (ft_get_time() - ref->philos[i].last_meal_time > (unsigned int)ref->life_time)
			ref->death_flag = ref->philos[i].philo_number;
		i++;
		if (i == ref->philos_number)
			i = 0;
	}
}

int	did_all_phlios_eat(t_data *ref)
{
	int	i;

	i = 0;
	if (ref->max_eat_times == -1)
		return (0);
	while (i < ref->philos_number)
	{
		if (ref->philos[i].meals_number < ref->max_eat_times)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data		data;

	if (!check_args(ac, av))
		return (1);
	initialize_data(&data, av, ac);
	if (data.max_eat_times == 0 || data.philos_number == 0)
		return (0);
	if (start_threads(&data, data.philos_number) == 1)
		return (1);
	while (!did_all_phlios_eat(&data))
	{
		if (data.death_flag != -1)
		{
			print_message("%lu\t%d died\n", &data, data.death_flag);
			data.status = 1;
			break ;
		}
	}
	return (free(data.philos), free(data.forks), 0);
}
