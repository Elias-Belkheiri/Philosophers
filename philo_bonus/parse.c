/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:29:52 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/13 14:28:20 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	initialize_forks(t_philosopher *philosopher, int n, t_philo_data *philo)
{
	philosopher->left_fork = philo->forks;
	if (n > 1)
		philosopher->right_fork = philo->forks;
	else
		philosopher->right_fork = NULL;
}

void	initialize_data(t_philosopher *philosopher, char **args)
{
	philosopher->time_to_die = ft_atoi(args[2]);
	philosopher->time_to_eat = ft_atoi(args[3]);
	philosopher->time_to_sleep = ft_atoi(args[4]);
	philosopher->time = 0;
	philosopher->count = 0;
	philosopher->id = 0;
	if (args[5])
		philosopher->how_much_to_eat = ft_atoi(args[5]);
	else
		philosopher->how_much_to_eat = 0;
}

int	initialize_philos_data(char **args, t_philo_data *philo,
							t_philosopher *philosopher)
{
	philo->num_of_philos = ft_atoi(args[1]);
	philo->philosophers = malloc(philo->num_of_philos * sizeof(pid_t));
	if (!philo->philosophers)
		return (0);
	sem_unlink("/tmp/print");
	sem_unlink("/tmp/forks");
	philosopher->print = sem_open("/tmp/print", O_CREAT, 777, 1);
	philo->forks = sem_open("/tmp/forks", O_CREAT, 777, philo->num_of_philos);
	initialize_data(philosopher, args);
	initialize_forks(philosopher, philo->num_of_philos, philo);
	return (1);
}
