/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:09:48 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/06 19:17:29 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"


int		ft_atoi(char *str)
{
	int i;
	int result;

	i = -1;
	result = 0;
	while (str && str[++i] == ' ');
	while (str && (str[i] >= '0' && str[i] <= '9'))
	{
		result *= 10;
		result = result + (str[i] - '0');
		i++;
	}
	return (result);
}

int	parsing(int argc, char **argv, t_tools *philo)
{
	philo->n_philos = ft_atoi(argv[1]);
	// printf("%d ", philo->n_philos);
	philo->time_die = ft_atoi(argv[2]);
	// printf("%d ", philo->time_die);
	philo->time_eat = ft_atoi(argv[3]);
	// printf("%d ", philo->time_eat);
	philo->time_sleep = ft_atoi(argv[4]);
	// printf("%d ", philo->time_sleep);
	if(argc == 6)
		philo->eat_number = ft_atoi(argv[5]);
	else
		philo->eat_number = -1;
	// printf("%d \n", philo->eat_number);
	if(philo->n_philos == 0 || philo->time_die < 60 || philo->time_eat < 60 || philo->time_sleep < 60 || philo->eat_number == 0)
	{
		printf("Incorrect Argument\nPlease enter valid tools.\n");
		return (1);
	}
	return (0);
}
// void	ft_sleep(t_philo *philo)
// {
// 	int time;

// 	time = philo->tools->time_sleep;
// 	struct timeval start;
// 	struct timeval end;
// 	gettimeofday(&start, NULL);
// 	while (1)
// 	{
// 		if(gettimeofday(&end, NULL) > start)
// 			printf("hello\n");
// 	}		
// }
void	*routine(void	*arg)
{
	t_philo *philo = (t_philo *)arg;
	if (philo->id % 2 != 1)
	{
		gettimeofday(&philo->t_now, 0);
		printf("%ld %d is thinking\n", (philo->t_now.tv_sec - philo->t_0.tv_sec)*1000 + (philo->t_now.tv_usec - philo->t_0.tv_usec)/1000, philo->id);
		usleep(philo->tools->time_eat * 1000);
		// ft_sleep(philo);
	}
	while(philo->tools->eat_number > philo->n_meal)
	{
		pthread_mutex_lock(&philo->tools->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->tools->forks[philo->right_fork]);
		gettimeofday(&philo->t_now, 0);
		printf("%ld %d has taken a fork\n", (philo->t_now.tv_sec - philo->t_0.tv_sec)*1000 + (philo->t_now.tv_usec - philo->t_0.tv_usec)/1000, philo->id);
		printf("%ld %d is eating\n", (philo->t_now.tv_sec - philo->t_0.tv_sec)*1000 + (philo->t_now.tv_usec - philo->t_0.tv_usec)/1000, philo->id);
		// philo->t_meal++;
		usleep(philo->tools->time_eat * 1000);
		philo->n_meal++;
		// philo->tools->eat_number--;
		// printf("----------%d\n",philo->n_meal);
		pthread_mutex_unlock(&philo->tools->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->tools->forks[philo->left_fork]);
		gettimeofday(&philo->t_now, 0);
		// if(philo->tools->eat_number <= philo->n_meal)
		// 	break;
		printf("%ld %d is sleeping\n", (philo->t_now.tv_sec - philo->t_0.tv_sec)*1000 + (philo->t_now.tv_usec - philo->t_0.tv_usec)/1000, philo->id);
		usleep(philo->tools->time_sleep * 1000);

		gettimeofday(&philo->t_now, 0);
		printf("%ld %d is thinking\n", (philo->t_now.tv_sec - philo->t_0.tv_sec)*1000 + (philo->t_now.tv_usec - philo->t_0.tv_usec)/1000, philo->id);
	}
	// printf(">>>>> %d\n", philo->tools->eat_number);
	// exit(0);
	return(NULL);
}

int init_philo(t_tools *tools)
{
	int i;
	i = 0;
	
	tools->philo = malloc(sizeof(t_philo) * tools->n_philos);
	if(!tools->philo)
		return (1);
	while (i < tools->n_philos)
	{
		tools->philo[i].id = i + 1;
		tools->philo[i].tools = tools;
		tools->philo[i].left_fork = i;
		tools->philo[i].n_meal = 0;
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
	while (i < tools->n_philos)
	{
		if(pthread_join(tools->philo[i].thread, NULL) != 0)
			return 1;
		i++;
	}
	return (0);
}




int main(int argc, char **argv)
{
	t_tools		*tools;
	// exit(0);
	// while(1);
	if(argc != 5 && argc != 6)
		return (1);
	tools = malloc(sizeof(t_tools) * 1);
	if(!tools || parsing(argc, argv, tools))
		return (1);
	if(init_philo(tools) || mutexes_and_threads(tools))
		return (1);

	// arg->forks = calloc(sizeof(pthread_mutex_t) , arg->n_philos);
	// if(!arg->forks)
	// 	return (1);

	return(0);
}
