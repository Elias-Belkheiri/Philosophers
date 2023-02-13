/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebelkhei <ebelkhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:30:49 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/02/13 14:44:21 by ebelkhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	int				n;
	t_philo_data	philo;

	if ((argc != 6 && argc != 5) || !check_args(argv))
		return (printf("Invalid Args\n"));
	if (!initialize_philos_data(argv, &philo))
		return (printf("Something's wrong\n"));
	n = -1;
	while (++n < philo.num_of_philos)
		pthread_create(&((philo.philosophers + n)->thread_id),
			NULL, routine, philo.philosophers + n);
	usleep(10);
	n = -1;
	if (!check_deaths(&philo))
	{
		while (++n < philo.num_of_philos)
			pthread_detach((philo.philosophers + n)->thread_id);
	}
	destroy_free(&philo);
}
