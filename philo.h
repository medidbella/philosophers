/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:44 by midbella          #+#    #+#             */
/*   Updated: 2024/05/17 16:58:32 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H 
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	unsigned long	last_meal_time;
	int				philo_number;
	int				meals_number;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				philos_number;
	int				life_time;
	int				eat_time;
	int				sleep_time;
	int				max_eat_times;
	int				death_flag;
	pthread_mutex_t	print_guard;
	pthread_mutex_t	*forks;
	unsigned long	t0;
}	t_data;

int	check_args(int ac, char **av);
int	ft_atoi(char *str);

#endif