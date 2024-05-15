/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:44 by midbella          #+#    #+#             */
/*   Updated: 2024/05/14 16:22:47 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H 
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
//it turns out that not every philo has his own fork but the subject
//only says that each philo has a fork on his left and right side and
//there are as many forks as the number of philosofers 
typedef struct s_fork
{
	int				fork;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned long	last_meal_time;
	int				philo_number;
	int				meals_number;
	t_fork			*r_fork;
	t_fork			*l_fork;
	void			*data;
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
	t_fork			*forks;
	unsigned long	t0;
}	t_data;

int	check_args(int ac, char **av);
int	ft_atoi(char *str);

#endif