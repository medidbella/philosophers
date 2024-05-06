/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:48 by midbella          #+#    #+#             */
/*   Updated: 2024/05/06 20:31:43 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void thread_function(t_data *ref)
{
	static int i;
	int g;

	printf("philosofer number %d is ready\n", ref->philos[i].philo_number);
	i++;
}

void	initialize_data(t_data *ref, char **av)
{
	int i;

	i = 0;
	ref->philos_number = ft_atoi(av[1]);
	ref->life_time = ft_atoi(av[2]);
	ref->eat_time = ft_atoi(av[3]);
	ref->sleep_time = ft_atoi(av[4]);
	if (av[5])
		ref->max_eat_time = ft_atoi(av[5]);
	else
		ref->max_eat_time = -1;
	ref->philos = malloc(sizeof(t_philo) * ref->philos_number);
	while (i <= ref->philos_number)
	{
		ref->philos[i].philo_number = i + 1;
		ref->philos[i].fork = 1;
		i++;
	}
}
void start_threads(t_data *data, int size)
{
	int i = 0;
	while (i < size)
	{
		pthread_create(&(data->philos[i].thread), NULL, (void *(*)(void *))thread_function, data);
		i++;
	}
	i--;
	while (i)
		pthread_join(data->philos[i--].thread, NULL);
}

int	main(int ac, char **av)
{
	pthread_mutex_t mute;
	t_data	prog_data;

	if (!check_args(ac, av))
		return (1);
	pthread_mutex_init(&mute, NULL);
	prog_data.mute = &mute;
	initialize_data(&prog_data, av);
	printf("philo nb = %d\nlife_time = %d\neat_time = %d\nsleep_time = %d\n",
		prog_data.philos_number ,prog_data.life_time , prog_data.eat_time ,prog_data.sleep_time);
	start_threads(&prog_data, prog_data.philos_number);
}
