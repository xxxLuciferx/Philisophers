/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:09:48 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/15 16:54:08 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:52:32 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/15 15:19:04 by khaimer          ###   ########.fr       */
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
					- start.tv_usec) / 1000) >= time)
			break ;
		gettimeofday(&end, NULL);
		usleep(200);
	}
}

int	time_calcule(t_philo *philo)
{
	int	time;

	gettimeofday(&philo->t_now, 0);
	time = (philo->t_now.tv_sec * 1000 + philo->t_now.tv_usec / 1000)
		- (philo->tools->t_start.tv_sec * 1000 + philo->tools->t_start.tv_usec
			/ 1000);
	return (time);
}

void	printer(t_philo *philo, char *line)
{
	pthread_mutex_lock(philo->tools->printing);
	printf("%d %d %s\n", time_calcule(philo), philo->id, line);
	pthread_mutex_unlock(philo->tools->printing);
	if (line[3] == 'e')
	{
		pthread_mutex_lock(philo->tools->printing);
		philo->n_meal++;
		pthread_mutex_unlock(philo->tools->printing);
		gettimeofday(&philo->tools->last_eat[philo->id - 1], 0);
		ft_sleep(philo->tools->time_eat);
	}
}

void	check_died(t_tools *tools)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(tools->printing);
		if (all_good(tools) == 1)
			return ;
		pthread_mutex_unlock(tools->printing);
		if (timer(&tools->philo[i]) >= tools->time_die)
		{
			pthread_mutex_lock(tools->printing);
			make_all_dead(tools->philo);
			printf("%d %d %s\n", time_calcule(tools->philo), tools->philo[i].id, "is died");
			return ;
		}
		i++;
		if (i == tools->n_philos)
			i = 0;
	}
	p_join(tools);
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
	check_died(tools);
	return (0);
}
