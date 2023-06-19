/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khaimer <khaimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:16:32 by khaimer           #+#    #+#             */
/*   Updated: 2023/06/15 17:26:09 by khaimer          ###   ########.fr       */
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
	pthread_mutex_t		*printing;
	pthread_mutex_t		*death;
	struct timeval		t_start;
	struct timeval		*last_eat;
}						t_tools;

typedef struct s_philo
{
	int					died;
	t_tools				*tools;
	pthread_t			thread;
	int					id;
	int					left_fork;
	int					right_fork;
	int					n_meal;
	struct timeval		t_now;
}						t_philo;

/* PARSING*/
int						ft_atoi(char *str);
int						parsing(int argc, char **argv, t_tools *philo);
int						init_philo(t_tools *tools);
int						one_philo(t_tools *tools);
int						mutexes_and_threads(t_tools *tools);

/*Philosophers*/
void					ft_sleep(int time);
int						time_calcule(t_philo *philo);
void					printer(t_philo *philo, char *line);
int						timer(t_philo *philo);
void					p_join(t_tools *tools);

/*dead_philo*/
void					make_all_dead(t_philo *philo);
int						all_good(t_tools *tools);
int						timer(t_philo *philo);
void					p_join(t_tools *tools);

/*tools*/
void					make_all_dead(t_philo *philo);
void					check_died(t_tools *tools);
void					*routine(void *arg);
void					mutex_destroy(t_tools *tools);

#endif