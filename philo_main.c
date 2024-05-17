/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:48 by midbella          #+#    #+#             */
/*   Updated: 2024/05/17 17:42:49 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time()
{
	struct timeval	curr;
	gettimeofday(&curr, NULL);
	return ((curr.tv_sec * 1000) + (curr.tv_usec / 1000));
}

void	message_printer(t_philo *ref)
{
	pthread_mutex_lock(&ref->data->print_guard);
	printf("%lu %d has taken a fork\n", ft_get_time() - ref->data->t0, ref->philo_number);
	printf("%lu %d has taken a fork\n", ft_get_time() - ref->data->t0, ref->philo_number);
	printf("%lu %d is eating\n", ft_get_time() - ref->data->t0, ref->philo_number);
	pthread_mutex_unlock(&ref->data->print_guard);
}
void	repititve_meal(t_philo *ref)
{
	pthread_mutex_lock(ref->l_fork);
	pthread_mutex_lock(ref->r_fork);
	message_printer(ref);
	usleep(ref->data->eat_time * 1000); 
	pthread_mutex_unlock(ref->r_fork);
	pthread_mutex_unlock(ref->l_fork);
}

void	thread_function(t_philo *ref)
{
	if (ref->philo_number % 2 == 0)
		usleep(2);
	while (1)
	{
		repititve_meal(ref);
		pthread_mutex_lock(&ref->data->print_guard);
		printf("%lu %d is sleeping\n", ft_get_time() - ref->data->t0, ref->philo_number);
		pthread_mutex_unlock(&ref->data->print_guard);
		usleep(ref->data->sleep_time);
		pthread_mutex_lock(&ref->data->print_guard);
		printf("%lu %d is thinking\n", ft_get_time() - ref->data->t0, ref->philo_number);
		pthread_mutex_unlock(&ref->data->print_guard);
	}
}

void	initialize_philos_forks(t_data *ref)
{
	int	r_fork_index;
	int	iter;

	iter = 1;
	ref->philos[iter].l_fork = &ref->forks[0];
	ref->philos[iter].r_fork = &ref->forks[ref->philos_number - 1];
	while (iter < ref->philos_number - 1)
	{
		ref->philos[iter].l_fork = &ref->forks[iter];
		ref->philos[iter].r_fork = &ref->forks[iter - 1];
		iter++;
	}
}

void	initialize_data(t_data *ref, char **av)
{
	int i;

	i = 0;
	ref->t0 = ft_get_time();
	ref->philos_number = ft_atoi(av[1]);
	ref->life_time = ft_atoi(av[2]);
	ref->eat_time = ft_atoi(av[3]);
	ref->sleep_time = ft_atoi(av[4]);
	ref->death_flag = -1;
	if (av[5])
		ref->max_eat_times = ft_atoi(av[5]);
	else
		ref->max_eat_times = -1;
	pthread_mutex_init(&ref->print_guard, NULL);
	ref->philos = malloc(sizeof(t_philo) * ref->philos_number);
	ref->forks = malloc(sizeof(pthread_mutex_t) * ref->philos_number);
	while (i <= ref->philos_number)
	{
		pthread_mutex_init((ref->philos[i].l_fork), NULL);
		ref->philos[i].philo_number = i +1;
		ref->philos[i].data = ref;
		ref->philos[i].meals_number = 0;
		i++;
	}
}

void start_threads(t_data *data, int size)
{
	int i = 0;
	while (i < size)
	{
		pthread_create(&(data->philos[i].thread), NULL,
			(void *(*)(void *))thread_function, &data->philos[i]);
		i++;
	}
	i--;
	while (i)
		pthread_detach(data->philos[i--].thread);
}

void	monitoring(t_data *ref)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((ft_get_time() - ref->t0) - ref->philos[i].last_meal_time >= ref->life_time)
			ref->death_flag = 1;
		i++;
		if (i == ref->philos_number)
			i = 0;
	}
}

int	did_all_phlios_eat(t_data *ref)
{
	int	i;
	
	i = 0;
	while (i < ref->philos_number)
	{
		if (ref->philos[i].meals_number != ref->max_eat_times)
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
	initialize_data(&prog_data, av);
	start_threads(&prog_data, prog_data.philos_number);
	pthread_create(&monitor, NULL, monitoring, &prog_data);
	pthread_detach(monitor);
	while (1)
	{
		if (did_all_phlios_eat(&prog_data))
			break ;
		else if (prog_data.death_flag != -1)
		{
			printf("philo nb %d died", prog_data.death_flag);
			break ;
		}
	}
	free(prog_data.philos);
	return (0);
}
