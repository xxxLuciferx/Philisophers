/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:20:12 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/15 17:26:07 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	make_all_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->tools->n_philos)
	{
		pthread_mutex_lock(philo->tools->death);
		philo[i].died = 1;
		pthread_mutex_unlock(philo->tools->death);
		i++;
	}
}

int	all_good(t_tools *tools)
{
	int	i;

	i = 0;
	if (tools->eat_number <= 0)
		return (0);
	while (i < tools->n_philos)
	{
		if (tools->philo[i].n_meal <= tools->eat_number)
			return (0);
		i++;
	}
	return (1);
}

int	timer(t_philo *philo)
{
	int				timing;
	struct timeval	time;

	gettimeofday(&time, 0);
	timing = ((time.tv_sec * 1000) + (time.tv_usec / 1000))
		- ((philo->tools->last_eat[philo->id - 1].tv_sec * 1000)
			+ (philo->tools->last_eat[philo->id - 1].tv_usec / 1000));
	return (timing);
}

void	p_join(t_tools *tools)
{
	int	i;

	i = 0;
	while (i < tools->n_philos)
	{
		pthread_join(tools->philo[i].thread, 0);
		i++;
	}
}

void	mutex_destroy(t_tools *tools)
{
	pthread_mutex_destroy(tools->forks);
	pthread_mutex_destroy(tools->printing);
	pthread_mutex_destroy(tools->death);
}
