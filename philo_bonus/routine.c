/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:31:02 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/13 14:30:42 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleep_think(t_philosopher *philo)
{
	sem_wait(philo->print);
	printf("Philosopher %d is sleeping in %ldms\n",
		philo->id, get_time() - philo->time);
	sem_post(philo->print);
	ft_sleep(philo->time_to_sleep);
	sem_wait(philo->print);
	printf("Philosopher %d is thinking in %ldms\n",
		philo->id, get_time() - philo->time);
	sem_post(philo->print);
}

void	eating(t_philosopher *philo)
{
	unsigned long	time;

	sem_wait(philo->print);
	gettimeofday(&philo->last_time_ate, NULL);
	time = (philo->last_time_ate.tv_sec * 1000)
		+ (philo->last_time_ate.tv_usec / 1000);
	printf("Philosopher %d is eating in %ldms\n", philo->id, time - philo->time);
	sem_post(philo->print);
	ft_sleep(philo->time_to_eat);
	sem_post(philo->right_fork);
	sem_post(philo->left_fork);
}

void	*check_death(void *tmp)
{
	t_philosopher	*philo;
	unsigned long	time;

	philo = tmp;
	while (1)
	{
		time = (philo->last_time_ate.tv_sec * 1000)
			+ (philo->last_time_ate.tv_usec / 1000);
		sem_wait(philo->print);
		if (!philo->right_fork || get_time() - time > philo->time_to_die)
		{
			printf("Philosopher %d died in %ld\n", philo->id,
				get_time() - philo->time);
			exit (1);
		}
		sem_post(philo->print);
	}
}

int	philo_is_eating(t_philosopher *philo)
{
	if (!philo->right_fork)
		return (0);
	sem_wait(philo->left_fork);
	sem_wait(philo->print);
	printf("Philosopher %d has taken a fork in %ldms\n", philo->id,
		get_time() - philo->time);
	sem_post(philo->print);
	sem_wait(philo->right_fork);
	sem_wait(philo->print);
	printf("Philosopher %d has taken a fork in %ldms\n", philo->id,
		get_time() - philo->time);
	sem_post(philo->print);
	eating(philo);
	return (1);
}

void	*routine(t_philosopher *philo)
{
	pthread_t	death;

	if (!(philo->id % 2))
		usleep(philo->time_to_eat);
	pthread_create(&death, NULL, check_death, philo);
	while (1)
	{
		if (philo_is_eating(philo))
		{
			if (philo->how_much_to_eat)
			{
				if (++(philo->count) == philo->how_much_to_eat)
				{
					sem_wait(philo->print);
					pthread_detach(death);
					exit(0);
				}
			}
			sleep_think(philo);
		}
	}
	return (NULL);
}
