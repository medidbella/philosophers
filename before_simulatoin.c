/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_simulatoin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:45:52 by midbella          #+#    #+#             */
/*   Updated: 2024/05/21 13:14:56 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialize_philos_forks(t_data *ref)
{
	int	r_fork_index;
	int	iter;

	iter = 1;
	ref->philos[0].last_meal_time = ref->t0;
	ref->philos[0].l_fork = &ref->forks[0];
	ref->philos[0].r_fork = &ref->forks[ref->philos_number - 1];
	while (iter < ref->philos_number)
	{
		ref->philos[iter].last_meal_time = ref->t0;
		ref->philos[iter].l_fork = &ref->forks[iter];
		ref->philos[iter].r_fork = &ref->forks[iter - 1];
		iter++;
	}
}

void	initialize_data(t_data *ref, char **av, int ac)
{
	int	i;

	i = 0;
	ref->t0 = ft_get_time();
	ref->philos_number = ft_atoi(av[1]);
	ref->life_time = ft_atoi(av[2]);
	ref->eat_time = ft_atoi(av[3]);
	ref->sleep_time = ft_atoi(av[4]);
	ref->death_flag = -1;
	if (ac == 6)
		ref->max_eat_times = ft_atoi(av[5]);
	else
		ref->max_eat_times = -1;
	pthread_mutex_init(&ref->print_guard, NULL);
	ref->philos = malloc(sizeof(t_philo) * ref->philos_number);
	ref->forks = malloc(sizeof(pthread_mutex_t) * ref->philos_number);
	initialize_philos_forks(ref);
	while (i < ref->philos_number)
	{
		pthread_mutex_init(&ref->forks[i], NULL);
		ref->philos[i].philo_number = i + 1;
		ref->philos[i].data = ref;
		ref->philos[i].meals_number = 0;
		i++;
	}
}

int	start_threads(t_data *data, int size)
{
	int	guard;
	int	i;

	i = 0;
	while (i < size)
	{
		guard = pthread_create(&(data->philos[i].thread), NULL,
				(void *(*)(void *))thread_function, &data->philos[i]);
		if (guard != 0)
			return (1);
		i++;
	}
	i--;
	while (i)
	{
		guard = pthread_detach(data->philos[i--].thread);
		if (guard != 0)
			return (1);
	}
	return (0);
}
