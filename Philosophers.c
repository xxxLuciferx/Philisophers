/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:09:48 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/13 10:50:08 by khaimer          ###   ########.fr       */
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
		usleep(150);
	}
}
int	time_calcule(t_philo *philo)
{
	int time;
	
	gettimeofday(&philo->t_now, 0);
	time = (philo->t_now.tv_sec * 1000 + philo->t_now.tv_usec / 1000) - (philo->tools->t_start.tv_sec * \
	1000 + philo->tools->t_start.tv_usec / 1000);
	return (time);
}
void	printer(t_philo *philo, char *line)
{
	// pthread_mutex_t	*print;
	
	// print = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_lock(print);
	
	printf("%d %d %s\n", time_calcule(philo), philo->id, line);
	if (line[3] == 'e')
	{
		gettimeofday(&philo->tools->last_eat[philo->id - 1], 0);
		philo->n_meal++;
		// usleep(10);
	}
	// pthread_mutex_unlock(print);
	// pthread_mutex_destroy(print);
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
void	check_died(t_tools *tools)
{
	int	i;

	i = 0;
	while (1)
	{
		if (timer(&tools->philo[i]) >= tools->time_die)
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
	return (0);
}
