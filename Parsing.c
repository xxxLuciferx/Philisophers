/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:30:08 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/14 23:22:10 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = -1;
	result = 0;
	while (str && str[++i] == ' ')
		;
	while (str && (str[i] >= '0' && str[i] <= '9'))
	{
		result *= 10;
		result = result + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (result);
}

int	parsing(int argc, char **argv, t_tools *philo)
{
	philo->n_philos = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->eat_number = ft_atoi(argv[5]);
	else
		philo->eat_number = -1;
	if (philo->n_philos == 0 || philo->time_die < 60 || philo->time_eat < 60
		|| philo->time_sleep < 60 || philo->eat_number == 0)
	{
		printf("Incorrect Argument\nPlease enter valid numbers.\n");
		return (1);
	}
	return (0);
}

int	init_philo(t_tools *tools)
{
	int	i;

	i = 0;
	tools->philo = malloc(sizeof(t_philo) * tools->n_philos);
	tools->last_eat = malloc(sizeof(struct timeval) * tools->n_philos);
	if (!tools->philo || !tools->last_eat)
		return (1);
	while (i < tools->n_philos)
	{
		tools->philo[i].id = i + 1;
		tools->philo[i].tools = tools;
		tools->philo[i].left_fork = i;
		tools->philo[i].n_meal = 0;
		tools->philo[i].died = 0;

		if (i > 0)
			tools->philo[i].right_fork = tools->philo[i - 1].id - 1;
		else
			tools->philo[i].right_fork = tools->n_philos - 1;
		i++;
	}
	gettimeofday(&tools->t_start, 0);
	return (0);
}

int	mutexes_and_threads(t_tools *tools)
{
	int	i;

	i = 0;
	tools->forks = malloc(sizeof(pthread_mutex_t) * tools->n_philos);
	tools->printing = malloc(sizeof(pthread_mutex_t));
	tools->death = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(tools->printing, NULL);
	pthread_mutex_init(tools->death, NULL);
	if (!tools->forks)
		return (1);
	while (i < tools->n_philos)
	{
		pthread_mutex_init(&tools->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < tools->n_philos)
	{
		if (pthread_create(&tools->philo->thread, NULL, &routine,
				&tools->philo[i]))
			return (1);
		i++;
	}
	return (0);
}
