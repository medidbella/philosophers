/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:44 by midbella          #+#    #+#             */
/*   Updated: 2024/05/06 19:35:33 by midbella         ###   ########.fr       */
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
	pthread_t	thread;
	int			philo_number;
	int			fork;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*mute;
	int				philos_number;
	int				life_time;
	int				eat_time;
	int				sleep_time;
	int				max_eat_time;
}	t_data;

int	check_args(int ac, char **av);
int	ft_atoi(char *str);

#endif