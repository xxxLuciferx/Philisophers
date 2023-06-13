/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:29:16 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/13 10:42:14 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		printer(philo, "is thinking");
	while (1)
	{
		if (philo->tools->eat_number != philo->n_meal)
		{
			pthread_mutex_lock(&philo->tools->forks[philo->left_fork]);
			printer(philo, "has taken a fork");
			pthread_mutex_lock(&philo->tools->forks[philo->right_fork]);
			printer(philo, "has taken a fork");
			printer(philo, "is eating");
			ft_sleep(philo->tools->time_eat);
			pthread_mutex_unlock(&philo->tools->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->tools->forks[philo->left_fork]);
			printer(philo, "is sleeping");
			ft_sleep(philo->tools->time_sleep);
			printer(philo, "is thinking");
		}
	}
	return (NULL);
}
