/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:48 by midbella          #+#    #+#             */
/*   Updated: 2024/05/13 12:37:53 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time()
{
	struct timeval	curr;
	gettimeofday(&curr, NULL);
	return ((curr.tv_sec * 1000) + (curr.tv_usec / 1000));
}

//make your own usleep beacause the og one is trash

void	diner_start(t_philo *taker, t_philo *borrower, int odd_even)
{
	t_data	*data = taker->data;

	pthread_mutex_lock(&(data->philos[0].mutex));
	if (odd_even == 1)
		pthread_mutex_unlock(&(data->philos[0].mutex));
	taker->fork++;
	borrower->data--;
	if (odd_even == 2)
		pthread_mutex_unlock(&(data->philos[0].mutex));
	pthread_mutex_lock(&(data->philos[0].mutex));
	if (odd_even == 2)
		pthread_mutex_unlock(&(data->philos[0].mutex);
}

void	first_diner(t_philo *taker, t_philo *borrower)
{
	t_data	*data = taker->data;

	borrower->fork--;
	taker->fork++;
	pthread_mutex_lock(&taker->mutex);
	printf("%lu %d has taken a fork\n", ft_get_time() - data->t0, taker->philo_number);
	printf("%lu %d has taken a fork\n", ft_get_time() - data->t0, taker->philo_number);
	printf("%lu %d is eating\n", ft_get_time() - data->t0, taker->philo_number);
	usleep(data->eat_time * 1000);
	pthread_mutex_unlock(&taker->mutex);
}

void	thread_function(t_philo *ref)
{
	t_data	*ptr;

	ptr = ref->data;
	if (ref->philo_number % 2 == 0)
		first_diner(ref, ref - 1);
	while (1)
	{
		if (ref->philo_number % 2 != 0)
		{
			if (ptr->philos_number == ref->philo_number)
				diner_start(ref, ptr->philos, 1);
			else
				diner_start(ref, ref + 1, 1);
		}
		else 
			diner_start(ref, ref - 1, 2);
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
	ref->philos = malloc(sizeof(t_philo) * ref->philos_number);
	while (i <= ref->philos_number)
	{
		ref->philos[i].philo_number = i + 1;
		ref->philos[i].fork = 1;
		ref->philos[i].data = ref;
		ref->philos[i].meals_number = 0;
		pthread_mutex_init(&(ref->philos[i].mutex), NULL);
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
		if ((ft_get_time() - ref->t0) - ref->philos[i].last_eat_time >= ref->eat_time)
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
	printf("philo nb = %d\nlife_time = %d\neat_time = %d\nsleep_time = %d\n",
		prog_data.philos_number, prog_data.life_time, prog_data.eat_time, prog_data.sleep_time);
	start_threads(&prog_data, prog_data.philos_number);
	//pthread_create(&monitor, NULL, monitoring, &prog_data);
	//pthread_detach(monitor);
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
