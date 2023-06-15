/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:29:16 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/14 23:25:39 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
 
	if (philo->id % 2 == 1)
	{
		printer(philo, "is thinking");
		ft_sleep(philo->tools->time_sleep);
	}
	while (1)
	{
			pthread_mutex_lock(&philo->tools->forks[philo->left_fork]);
			printer(philo, "has taken a fork");
			pthread_mutex_lock(&philo->tools->forks[philo->right_fork]);
			printer(philo, "has taken a fork");
			printer(philo, "is eating");

			pthread_mutex_unlock(&philo->tools->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->tools->forks[philo->left_fork]);
			printer(philo, "is sleeping");
			ft_sleep(philo->tools->time_sleep);
			printer(philo, "is thinking");
			pthread_mutex_lock(philo->tools->death);
			// if(philo->died == 1)
			// 	return NULL;
			pthread_mutex_unlock(philo->tools->death);
	}
	return (NULL);
}
