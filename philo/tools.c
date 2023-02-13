/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:17:36 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/13 13:47:10 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_sleep(int time)
{
	unsigned long	start;

	start = get_time();
	while (get_time() < start + time)
		usleep(100);
}

void	print_data(t_philo_data *philo)
{
	int	i;

	i = -1;
	while (++i < philo->num_of_philos)
		printf("Mutex: %p\n", philo->forks + i);
	printf("----------\n");
	i = -1;
	while (++i < philo->num_of_philos)
	{
		printf("Philosopher Number: %d\n", ((philo->philosophers) + i)->id);
		printf("Left Mutex %p\n", ((philo->philosophers) + i)->left_fork);
		printf("Right Mutex %p\n", ((philo->philosophers) + i)->right_fork);
		printf("Last time ate: %lu\n",
			((philo->philosophers) + i)->last_time_ate);
		printf("Time to eat: %lu\n", ((philo->philosophers) + i)->time_to_eat);
		printf("Time to sleep: %lu\n",
			((philo->philosophers) + i)->time_to_sleep);
		printf("How Much to eat: %d\n",
			((philo->philosophers) + i)->how_much_to_eat);
		printf("Time: %ld\n", *((philo->philosophers) + i)->time);
		printf("----------\n");
	}
}

void	destroy_free(t_philo_data *philo)
{
	int	i;

	i = -1;
	while (++i < philo->num_of_philos)
		pthread_mutex_destroy(philo->forks + i);
	free(philo->philosophers);
	free(philo->forks);
	free(philo->finished);
	free(philo->philosophers->print);
	free(philo->philosophers->time);
}

void	set_time(t_philosopher *philo)
{
	pthread_mutex_lock(philo->print);
	if (!*(philo->time))
		*(philo->time) = get_time();
	pthread_mutex_unlock(philo->print);
}
