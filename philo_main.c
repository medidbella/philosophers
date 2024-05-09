/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:48 by midbella          #+#    #+#             */
/*   Updated: 2024/05/09 17:40:57 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_get_time()
{
	struct timeval	curr;
	gettimeofday(&curr, NULL);
	return ((curr.tv_sec * 1000) + (curr.tv_usec / 1000));
}

void	hold_fork(t_philo *ref)
{
	return ;
}
void	eating_state(t_philo *ref)
{	
	hold_fork(ref);
	printf("%lu philsofer %d has taken a fork", ft_get_time, ref->philo_number);
}

void	thread_function(t_philo *ref)
{
	if (ref->philo_number % 2 != 0)
		eating_state(ref);
}

void	initialize_data(t_data *ref, char **av)
{
	int i;

	i = 0;
	ref->philos_number = ft_atoi(av[1]);
	ref->life_time = ft_atoi(av[2]);
	ref->eat_time = ft_atoi(av[3]);
	ref->sleep_time = ft_atoi(av[4]);
	ref->death_flag = 0;
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
		pthread_join(data->philos[i--].thread, NULL);
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
	t_data	prog_data;

	if (!check_args(ac, av))
		return (1);
	initialize_data(&prog_data, av);
	printf("philo nb = %d\nlife_time = %d\neat_time = %d\nsleep_time = %d\n",
		prog_data.philos_number, prog_data.life_time, prog_data.eat_time, prog_data.sleep_time);
	start_threads(&prog_data, prog_data.philos_number);
	while (1)
	{
		if (!prog_data.death_flag && did_all_phlios_eat(&prog_data))
			break ;
	}
	free(prog_data.philos);
}

// int main()
// {
// 	unsigned long time;
// 	unsigned long end;

// 	time = ft_get_time();
// 	usleep(5000);
// 	end = ft_get_time();
// 	printf("sleep time = %lu", end - time);
// }
