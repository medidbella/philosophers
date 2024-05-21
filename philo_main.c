/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:48 by midbella          #+#    #+#             */
/*   Updated: 2024/05/21 13:12:49 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	repititve_meal(t_philo *ref)
{
	pthread_mutex_lock(ref->l_fork);
	pthread_mutex_lock(ref->r_fork);
	pthread_mutex_lock(&ref->data->print_guard);
	printf("%lu %d has taken a fork\n", ft_get_time() - ref->data->t0,
		ref->philo_number);
	printf("%lu %d has taken a fork\n", ft_get_time() - ref->data->t0,
		ref->philo_number);
	printf("%lu %d is eating\n", ft_get_time() - ref->data->t0,
		ref->philo_number);
	pthread_mutex_unlock(&ref->data->print_guard);
	ref->last_meal_time = ft_get_time();
	ref->meals_number += 1;
	ft_sleep(ref->data->eat_time);
	pthread_mutex_unlock(ref->r_fork);
	pthread_mutex_unlock(ref->l_fork);
}

void	thread_function(t_philo *ref)
{
	if (ref->philo_number % 2 == 0)
		usleep(5);
	while (1)
	{
		repititve_meal(ref);
		pthread_mutex_lock(&ref->data->print_guard);
		printf("%lu %d is sleeping\n", ft_get_time() - ref->data->t0,
			ref->philo_number);
		pthread_mutex_unlock(&ref->data->print_guard);
		ft_sleep(ref->data->sleep_time);
		pthread_mutex_lock(&ref->data->print_guard);
		printf("%lu %d is thinking\n", ft_get_time() - ref->data->t0,
			ref->philo_number);
		pthread_mutex_unlock(&ref->data->print_guard);
	}
}

void	monitoring(t_data *ref)
{
	int	i;

	i = 0;
	while (1)
	{
		if (ft_get_time() - ref->philos[i].last_meal_time > ref->life_time)
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
	t_data		prog_data;
	pthread_t	monitor;

	if (!check_args(ac, av))
		return (1);
	initialize_data(&prog_data, av, ac);
	if (prog_data.max_eat_times == 0 || prog_data.philos_number == 0)
		return (0);
	if (start_threads(&prog_data, prog_data.philos_number) == 1)
		return (1);
	if (pthread_create(&monitor, NULL, (void *)monitoring, &prog_data) != 0)
		return (1);
	if (pthread_detach(monitor) != 0)
		return (1);
	while (!did_all_phlios_eat(&prog_data))
	{
		if (prog_data.death_flag != -1)
		{
			pthread_mutex_lock(&prog_data.print_guard);
			printf("%lu %d died\n", ft_get_time() - prog_data.t0,
				prog_data.death_flag);
			break ;
		}
	}
	return (free(prog_data.philos), free(prog_data.forks), 0);
}
