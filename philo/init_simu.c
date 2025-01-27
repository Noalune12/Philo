/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:41:19 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/27 10:07:12 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex_simu(t_simulation *simu)
{
	if (pthread_mutex_init(&simu->msg_mutex, NULL) != 0)
		return (destroy_mutex(simu, 0, -1));
	if (pthread_mutex_init(&simu->meal_mutex, NULL) != 0)
		return (destroy_mutex(simu, 1, -1));
	if (pthread_mutex_init(&simu->dead_mutex, NULL) != 0)
		return (destroy_mutex(simu, 2, -1));
	if (pthread_mutex_init(&simu->thread_mutex, NULL) != 0)
		return (destroy_mutex(simu, 3, -1));
	return (0);
}

int	init_simulation(t_simulation *simu, t_philo *philo, char **argv)
{
	simu->dead = 0;
	simu->thread_fail = -1;
	simu->nb_philos = ft_atoi(argv[1]);
	if (init_mutex_simu(simu) == 1)
	{
		printf("Failed to initialize mutex\n");
		return (1);
	}
	simu->philo = philo;
	return (0);
}
