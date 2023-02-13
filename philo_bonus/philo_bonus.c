/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:41:41 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/13 14:43:03 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_philosopher	philosopher;
	t_philo_data	philo;
	int				n;

	if ((argc != 6 && argc != 5) || !check_args(argv))
		return (printf("Invalid Args\n"));
	if (!initialize_philos_data(argv, &philo, &philosopher))
		return (printf("Something's wrong\n"));
	n = -1;
	while (++n < philo.num_of_philos)
	{
		set_info(&philosopher);
		*(philo.philosophers + n) = fork();
		if (!(philo.philosophers[n]))
		{
			routine(&philosopher);
			return (0);
		}
	}
	finish(&philosopher, &philo);
}
