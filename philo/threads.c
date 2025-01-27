/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:41:34 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/27 09:44:33 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philo(t_philo *philo, t_simulation *simu)
{
	if (pthread_create(&philo->thread, NULL, &one_philo_routine, philo) != 0)
		return (error_msg("Thread creation failed\n", simu));
	if (pthread_join(philo->thread, NULL) != 0)
		return (error_msg("Thread join failed\n", simu));
	return (0);
}

static int	join_threads(t_simulation *simu, pthread_t	monitor_thread,
		int index, int fail)
{
	int	i;

	i = 0;
	if (pthread_join(monitor_thread, NULL) != 0)
	{
		fail = 2;
		pthread_mutex_lock(&simu->dead_mutex);
		simu->dead = 1;
		pthread_mutex_unlock(&simu->dead_mutex);
	}
	while (i < index)
	{
		if (pthread_join(simu->philo[i].thread, NULL) != 0)
			fail = 2;
		i++;
	}
	if (fail == 2)
		return (error_msg("Thread join failed\n", simu));
	if (fail == 1)
		return (1);
	return (0);
}

static int	create_threads_loop(t_simulation *simu, int *fail, int i)
{
	if (pthread_create(&simu->philo[i].thread, NULL,
			&philo_routine, &simu->philo[i]) != 0)
	{
		*fail = 1;
		pthread_mutex_lock(&simu->thread_mutex);
		simu->thread_fail = FAIL;
		pthread_mutex_unlock(&simu->thread_mutex);
		error_msg("Thread creation failed\n", simu);
		return (1);
	}
	return (0);
}

int	create_threads(t_simulation *simu)
{
	int			i;
	int			fail;
	pthread_t	monitor_thread;

	if (simu->nb_philos == 1)
		return (one_philo(&simu->philo[0], simu));
	if (pthread_create(&monitor_thread, NULL, monitor_philo, simu->philo) != 0)
		return (error_msg("Thread creation failed\n", simu));
	i = 0;
	fail = 0;
	while (i < simu->nb_philos)
	{
		if (create_threads_loop(simu, &fail, i) == 1)
			break ;
		i++;
	}
	if (fail == 0)
	{
		pthread_mutex_lock(&simu->thread_mutex);
		simu->thread_fail = SUCCESS;
		pthread_mutex_unlock(&simu->thread_mutex);
	}
	if (join_threads(simu, monitor_thread, i, fail) == 1)
		return (1);
	return (0);
}
