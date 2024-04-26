/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midbella <midbella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 20:50:44 by midbella          #+#    #+#             */
/*   Updated: 2024/04/25 21:42:16 by midbella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H 
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int	philo_number;
	int	forks;
	int	life_time;
	int	eat_time;
	int	sleep_time;
	int max_eat_time;
}	t_data;

int	check_args(int ac, char **av);
int	ft_atoi(const char *str);

#endif