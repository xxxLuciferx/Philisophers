/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:09:48 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/10 17:49:06 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	ft_sleep(int time)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	while (1)
	{
		if (((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec
					- start.tv_usec) / 1000) == time)
			break ;
		gettimeofday(&end, NULL);
		usleep(10);
	}
}

void	printer(t_philo *philo, char *line)
{
	pthread_mutex_t	*print;
	
	print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_lock(print);
	gettimeofday(&philo->t_now, 0);
	printf("%ld %d %s\n", (philo->t_now.tv_sec * 1000 + \
	philo->t_now.tv_usec / 1000) - (philo->tools->t_start.tv_sec * \
	1000 + philo->tools->t_start.tv_usec / 1000), philo->id, line);
	if (line[3] == 'e')
	{
		usleep(10);
		gettimeofday(&philo->tools->last_eat[philo->id - 1], 0);
		philo->n_meal++;
	}
	if (line[3] == 't')
		ft_sleep(philo->tools->time_sleep);
	pthread_mutex_unlock(print);
}

int	timer(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000))
		- ((philo->tools->last_eat[philo->id - 1].tv_sec * 1000)
			+ (philo->tools->last_eat[philo->id - 1].tv_usec / 1000)));
}

void	check_died(t_tools *tools)
{
	int	i;

	i = 0;
	while (1)
	{
		if (timer(&tools->philo[i]) > tools->time_die + 10
			|| tools->n_philos == 1)
		{
			printer(&tools->philo[i], "is died");
			return ;
		}
		else if (tools->philo->n_meal == tools->eat_number)
			return ;
		i++;
		if (i == tools->n_philos)
			i = 0;
	}
}

int	main(int argc, char **argv)
{
	t_tools	*tools;

	if (argc != 5 && argc != 6)
		return (1);
	tools = malloc(sizeof(t_tools) * 1);
	if (!tools || parsing(argc, argv, tools))
		return (1);
	if (init_philo(tools) || mutexes_and_threads(tools))
		return (1);
	return (0);
}
