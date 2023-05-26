/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:16:32 by khaimer           #+#    #+#             */
/*   Updated: 2023/05/26 00:09:41 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS
# define	PHILOSOPHERS

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo t_philo;

typedef struct s_tools
{
	t_philo	*philo;
	int n_philos;
	int time_die;
	int time_eat;
	int time_sleep;
	int eat_number;
	pthread_mutex_t *forks;
}t_tools;

typedef struct s_philo
{
	t_tools 		*tools;
	int 			id;
	pthread_t		thread;
	int 			left_fork;
	int				right_fork;
	int				meal_numbers;
	struct timeval	t_0;
	struct timeval	t_now;
}t_philo;

#endif