/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:17:36 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/13 14:40:12 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	set_info(t_philosopher *philosopher)
{
	if (!philosopher->time)
			philosopher->time = get_time();
	philosopher->id++;
	gettimeofday(&philosopher->last_time_ate, NULL);
}

void	finish(t_philosopher *philosopher, t_philo_data *philo)
{
	int	status;
	int	n;

	n = -1;
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 1)
		{
			while (++n < philo->num_of_philos)
				kill(philo->philosophers[n], SIGINT);
		}
		if (WEXITSTATUS(status) == 0)
			sem_post(philosopher->print);
	}
	sem_close(philo->forks);
	sem_close(philosopher->print);
	free(philo->philosophers);
}
