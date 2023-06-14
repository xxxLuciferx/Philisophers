/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:09:48 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/14 23:14:03 by khaimer          ###   ########.fr       */
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
		if (((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec - start.tv_usec) / 1000) >= time)
			break ;
		gettimeofday(&end, NULL);
		usleep(200);
	}
}
int	time_calcule(t_philo *philo)
{
	// int time;
	
	gettimeofday(&philo->t_now, 0);

	return ((philo->t_now.tv_sec * 1000 + philo->t_now.tv_usec / 1000) - (philo->tools->t_start.tv_sec * \
	1000 + philo->tools->t_start.tv_usec / 1000));
}
void	printer(t_philo *philo, char *line)
{
	printf("%d %d %s\n", time_calcule(philo), philo->id, line);
	if (line[3] == 'e')
	{
		gettimeofday(&philo->tools->last_eat[philo->id - 1], 0);
		pthread_mutex_lock(philo->tools->printing);
		philo->n_meal++;
		pthread_mutex_unlock(philo->tools->printing);
	}
}

int	timer(t_philo *philo)
{
	struct timeval	time;
	int timing;
	gettimeofday(&time, 0);
	timing = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - ((philo->tools->last_eat[philo->id - 1].tv_sec * 1000) + (philo->tools->last_eat[philo->id - 1].tv_usec / 1000));
	return (timing);
}
void	p_join(t_tools *tools)
{
	int i;

	i = 0;
	while (i < tools->n_philos)
	{
		pthread_join(tools->philo[i].thread, 0);
		i++;
	}
	
}

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
		{
			return (0);
		}
		i++;
	}
	return (1);
}
void	check_died(t_tools *tools)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(tools->printing);
		if(all_good(tools) == 1)
			return ;
		pthread_mutex_unlock(tools->printing);
		if (timer(&tools->philo[i]) >= tools->time_die)
		{
			pthread_mutex_lock(tools->printing);
			printer(&tools->philo[i], "died");
			make_all_dead(tools->philo);
			return ;
		}
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
	check_died(tools);
	return (0);
}
