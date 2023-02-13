/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:29:52 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/13 13:45:37 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!(args[i][j] >= '0' && args[i][j] <= '9')
				|| ft_atoi(args[i]) <= 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	initialize_forks(t_philosopher *philosophers,
						int n, t_philo_data *philo)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (n == 1)
		{
			(philosophers + i)->left_fork = philo->forks;
			(philosophers + i)->right_fork = NULL;
			return ;
		}
		else if (i == n - 1)
		{
			(philosophers + i)->left_fork = philo->forks + i;
			(philosophers + i)->right_fork = philo->forks;
		}
		else
		{
			(philosophers + i)->left_fork = philo->forks + i;
			(philosophers + i)->right_fork = philo->forks + i + 1;
		}
	}	
}

void	initialize_data(t_philo_data *philo, pthread_mutex_t *print,
						unsigned long *time, char **args)
{
	int	i;

	i = -1;
	while (++i < philo->num_of_philos)
	{
		pthread_mutex_init(philo->forks + i, NULL);
		(philo->philosophers + i)->last_time_ate = 0;
		(philo->philosophers + i)->time_to_die = ft_atoi(args[2]);
		(philo->philosophers + i)->time_to_eat = ft_atoi(args[3]);
		(philo->philosophers + i)->time_to_sleep = ft_atoi(args[4]);
		(philo->philosophers + i)->print = print;
		(philo->philosophers + i)->time = time;
		(philo->philosophers + i)->id = i + 1;
		(philo->philosophers + i)->count = 0;
		(philo->philosophers + i)->state = 1;
		(philo->philosophers + i)->finished = philo->finished;
		if (args[5])
			(philo->philosophers + i)->how_much_to_eat = ft_atoi(args[5]);
		else
			(philo->philosophers + i)->how_much_to_eat = 0;
	}
}

int	initialize_philos_data(char **args, t_philo_data *philo)
{
	pthread_mutex_t	*print;
	unsigned long	*time;
	int				i;

	philo->num_of_philos = ft_atoi(args[1]);
	philo->philosophers = malloc(philo->num_of_philos * sizeof(t_philosopher));
	philo->forks = malloc(philo->num_of_philos * sizeof(pthread_mutex_t));
	print = malloc(sizeof(pthread_mutex_t));
	time = malloc(sizeof(unsigned long));
	philo->finished = malloc(sizeof(int));
	if (!philo->philosophers || !philo->forks
		||!print || !time || !philo->finished)
		return (0);
	i = -1;
	*time = 0;
	*philo->finished = 0;
	pthread_mutex_init(print, NULL);
	initialize_data(philo, print, time, args);
	initialize_forks(philo->philosophers, philo->num_of_philos, philo);
	return (1);
}
