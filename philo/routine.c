/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:31:02 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/13 13:47:04 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_think(t_philosopher *philo)
{
	pthread_mutex_lock(philo->print);
	printf("Philosopher %d is sleeping in %ldms\n",
		philo->id, get_time() - *(philo->time));
	pthread_mutex_unlock(philo->print);
	ft_sleep(philo->time_to_sleep);
	pthread_mutex_lock(philo->print);
	printf("Philosopher %d is thinking in %ldms\n",
		philo->id, get_time() - *(philo->time));
	pthread_mutex_unlock(philo->print);
}

int	check_deaths(t_philo_data *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == philo->num_of_philos)
			i = 0;
		pthread_mutex_lock((philo->philosophers + i)->print);
		if (*philo->finished == philo->num_of_philos)
			return (1);
		if (!(philo->philosophers + i)->right_fork
			|| get_time() - *((philo->philosophers + i)->time)
			- (philo->philosophers + i)->last_time_ate
			> (philo->philosophers + i)->time_to_die)
		{
			printf("Philosopher %d died in %ld\n", (philo->philosophers + i)->id,
				get_time() - *((philo->philosophers + i)->time));
			return (0);
		}
		pthread_mutex_unlock((philo->philosophers + i)->print);
		i++;
	}
	return (1);
}

void	eating(t_philosopher *philo)
{
	unsigned long	time;

	pthread_mutex_lock(philo->print);
	time = get_time() - *(philo->time);
	philo->last_time_ate = time;
	pthread_mutex_unlock(philo->print);
	printf("Philosopher %d is eating in %ldms\n", philo->id, time);
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

int	philo_is_eating(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->print);
	printf("Philosopher %d has taken a fork in %ldms\n", philo->id,
		get_time() - *(philo->time));
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->print);
	printf("Philosopher %d has taken a fork in %ldms\n", philo->id,
		get_time() - *(philo->time));
	pthread_mutex_unlock(philo->print);
	eating(philo);
	return (1);
}

void	*routine(void *tmp)
{
	t_philosopher	*philo;

	philo = tmp;
	if (!(philo->id % 2))
		usleep(philo->time_to_eat);
	set_time(philo);
	while (1)
	{
		if (!philo->right_fork)
			return (NULL);
		philo_is_eating(philo);
		if (philo->how_much_to_eat)
		{
			if (++(philo->count) == philo->how_much_to_eat)
			{
				pthread_mutex_lock(philo->print);
				(*philo->finished)++;
				pthread_mutex_unlock(philo->print);
				pthread_detach(philo->thread_id);
				return (NULL);
			}
		}
		sleep_think(philo);
	}
	return (NULL);
}
