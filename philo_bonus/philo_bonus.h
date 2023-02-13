/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:42:15 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/13 13:53:44 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <semaphore.h>
# include <time.h>

typedef struct philosopher
{
	unsigned long	time;
	struct timeval	last_time_ate;
	unsigned long	time_to_sleep;
	unsigned long	time_to_eat;
	unsigned long	time_to_die;
	sem_t			*right_fork;
	sem_t			*left_fork;
	sem_t			*print;
	int				how_much_to_eat;
	int				count;
	int				id;
}	t_philosopher;

typedef struct philodata
{
	pid_t	*philosophers;
	sem_t	*forks;
	int		num_of_philos;
}	t_philo_data;

long long		ft_atoi(const char *str);
int				initialize_philos_data(char **args, t_philo_data *philo,
					t_philosopher *philosopher);
int				check_args(char **args);
void			print_data(t_philo_data *philo);
unsigned long	get_time(void);
int				philo_is_eating(t_philosopher *philo);
void			ft_sleep(int time);
void			*routine(t_philosopher *tmp);
void			*check_death(void *tmp);
void			initialize_data(t_philosopher *philosopher, char **args);
void			set_info(t_philosopher *philosopher);
void			finish(t_philosopher *philosopher, t_philo_data *philo);

#endif