/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:41:00 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/13 13:47:27 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <time.h>

typedef struct philosopher
{
	pthread_t		thread_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print;
	unsigned long	*time;
	unsigned long	last_time_ate;
	unsigned long	time_to_sleep;
	unsigned long	time_to_eat;
	unsigned long	time_to_die;
	int				how_much_to_eat;
	int				*finished;
	int				count;
	int				state;
	int				id;
}	t_philosopher;

typedef struct philodata
{
	t_philosopher		*philosophers;
	pthread_mutex_t		*forks;
	int					*finished;
	int					num_of_philos;
}	t_philo_data;

long long		ft_atoi(const char *str);
int				initialize_philos_data(char **args, t_philo_data *philo);
int				check_args(char **args);
void			print_data(t_philo_data *philo);
unsigned long	get_time(void);
int				philo_is_eating(t_philosopher *philo);
void			ft_sleep(int time);
void			*routine(void *tmp);
int				check_deaths(t_philo_data *philo);
void			destroy_free(t_philo_data *philo);
void			set_time(t_philosopher *philo);

#endif
