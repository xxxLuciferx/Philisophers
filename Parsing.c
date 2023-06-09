/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:30:08 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/09 23:34:17 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	ft_atoi(char *str)
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
	if(str[i] != '\0')
		return (0);
	return (result);
}

int	parsing(int argc, char **argv, t_tools *philo)
{
	philo->n_philos = ft_atoi(argv[1]);
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		philo->eat_number = ft_atoi(argv[5]);
	else
		philo->eat_number = -1;
	if(philo->n_philos == 0 || philo->time_die < 60 || philo->time_eat < 60 || philo->time_sleep < 60 || philo->eat_number == 0)
	{
		printf("Incorrect Argument\nPlease enter valid tools.\n");
		return (1);
	}
	return (0);
}