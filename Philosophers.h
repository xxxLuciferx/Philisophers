/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:16:32 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/13 10:46:17 by khaimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_tools
{
	t_philo				*philo;
	int					n_philos;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					eat_number;
	pthread_mutex_t		*forks;
	struct timeval		t_start;
	struct timeval		*last_eat;
}						t_tools;

typedef struct s_philo
{
	t_tools				*tools;
	pthread_t			thread;
	int					id;
	int					left_fork;
	int					right_fork;
	int					n_meal;
	struct timeval		t_now;
}						t_philo;

int						ft_atoi(char *str);
int						parsing(int argc, char **argv, t_tools *philo);
int						init_philo(t_tools *tools);
int						mutexes_and_threads(t_tools *tools);
void					ft_sleep(int time);
void					printer(t_philo *philo, char *line);
int						timer(t_philo *philo);
void					check_died(t_tools *tools);
void					*routine(void *arg);

#endif