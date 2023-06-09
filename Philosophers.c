/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:09:48 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/09 23:40:57 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	ft_sleep(int time)
{
	struct timeval start;
	struct timeval end;

	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);

	while (1)
	{
		if(((end.tv_sec - start.tv_sec) * 1000) + ((end.tv_usec - start.tv_usec) / 1000) == time)
			break;
		gettimeofday(&end, NULL);
		usleep(70);
	}
	// usleep(150);
}

void	printer(t_philo *philo, char *line)
{
	gettimeofday(&philo->t_now, 0);
	printf("%ld %d %s\n", (philo->t_now.tv_sec*1000 + philo->t_now.tv_usec/1000) - (philo->t_0.tv_sec*1000 + philo->t_0.tv_usec/1000), philo->id, line);
	if(line[3] == 'e')
		gettimeofday(&philo->tools->last_eat[philo->id - 1], 0);
}

int	timer(t_philo *philo)
{
	struct timeval time;
	gettimeofday(&time, 0);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - ((philo->tools->last_eat[philo->id - 1].tv_sec * 1000) + (philo->tools->last_eat[philo->id - 1].tv_usec / 1000)));
}

void	*routine(void	*arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 1 && philo->tools->n_philos > 1)
	{
		printer(philo, "is thinking");
		ft_sleep(philo->tools->time_sleep);
	}
	while(1)
	{
		if(philo->tools->eat_number != philo->n_meal && philo->tools->n_philos > 1)
		{	
			pthread_mutex_lock(&philo->tools->forks[philo->left_fork]);
			pthread_mutex_lock(&philo->tools->forks[philo->right_fork]);
			printer(philo, "has taken a fork");
			printer(philo, "is eating");
			ft_sleep(philo->tools->time_eat);
			philo->n_meal++;
			pthread_mutex_unlock(&philo->tools->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->tools->forks[philo->left_fork]);
			printer(philo, "is sleeping");
			ft_sleep(philo->tools->time_sleep);
			printer(philo, "is thinking");
		}
	}
	return(NULL);
}

int init_philo(t_tools *tools)
{
	int i;
	i = 0;

	tools->philo = malloc(sizeof(t_philo) * tools->n_philos);
	tools->last_eat = malloc(sizeof(struct timeval)*tools->n_philos);
	if(!tools->philo)
		return (1);
	while (i < tools->n_philos)
	{
		tools->philo[i].id = i + 1;
		tools->philo[i].tools = tools;
		tools->philo[i].left_fork = i;
		tools->philo[i].n_meal = 0;
		gettimeofday(&tools->last_eat[i], 0);
		gettimeofday(&tools->philo[i].t_0, 0);
		if(i > 0)
			tools->philo[i].right_fork = tools->philo[i - 1].id - 1;
		else
			tools->philo[i].right_fork = tools->n_philos - 1;
		i++;
	}
	return(0);
}

int	mutexes_and_threads(t_tools *tools)
{
	int	i;

	i = 0;
	tools->forks = malloc(sizeof(pthread_mutex_t) * tools->n_philos);
	if(!tools->forks)
		return (1);
	while (i < tools->n_philos)
	{
		pthread_mutex_init(&tools->forks[i],NULL);
		i++;
	}
	i = 0;
	while (i < tools->n_philos)
	{
		if(pthread_create(&tools->philo->thread, NULL, &routine, &tools->philo[i]))
			return 1;
		i++;
	}
	i = 0;
	while(1)
	{
		if (timer(&tools->philo[i]) > tools->time_die + 10|| tools->n_philos == 1)
		{
			printer(&tools->philo[i], "is died");
			return 0;
		}
		else if(tools->philo->n_meal == tools->eat_number)
			return 0;
		i++;
		if (i == tools->n_philos)
			i = 0;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_tools		*tools;
	
	if(argc != 5 && argc != 6)
		return (1);
	tools = malloc(sizeof(t_tools) * 1);
	if(!tools || parsing(argc, argv, tools))
		return (1);
	if(init_philo(tools) || mutexes_and_threads(tools))
		return (1);

	return (0);
}
