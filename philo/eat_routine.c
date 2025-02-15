/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:41:12 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/27 11:10:33 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->lfork_mut);
	if (philo->left_fork == AVAILABLE)
	{
		philo->left_fork = TAKEN;
		pthread_mutex_unlock(&philo->lfork_mut);
		print_msg(GREEN"has taken a fork"RESET, philo, philo->id);
		++philo->left_fork_taken;
		return (1);
	}
	pthread_mutex_unlock(&philo->lfork_mut);
	if (philo->left_fork_taken == 1)
		return (1);
	return (0);
}

static int	right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->rfork_mut);
	if (*(philo->right_fork) == AVAILABLE)
	{
		*(philo->right_fork) = TAKEN;
		pthread_mutex_unlock(philo->rfork_mut);
		print_msg(GREEN"has taken a fork"RESET, philo, philo->id);
		++philo->right_fork_taken;
		return (1);
	}
	pthread_mutex_unlock(philo->rfork_mut);
	if (philo->right_fork_taken == 1)
		return (1);
	return (0);
}

static int	take_forks(t_philo *philo)
{
	if (right_fork(philo) == 0)
		return (0);
	if (left_fork(philo) == 0)
		return (0);
	if (philo->left_fork_taken == 1 && philo->right_fork_taken == 1)
		return (1);
	return (0);
}

int	eat_philo(t_philo *philo)
{
	while (take_forks(philo) == 0)
		ft_usleep(1, philo);
	pthread_mutex_lock(philo->meal_mutex);
	philo->eating = 1;
	philo->last_eaten = get_current_time();
	pthread_mutex_unlock(philo->meal_mutex);
	print_msg(YELLOW"is eating"RESET, philo, philo->id);
	ft_usleep(philo->eat_time, philo);
	pthread_mutex_lock(philo->meal_mutex);
	philo->eating = 0;
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_mutex);
	pthread_mutex_lock(philo->rfork_mut);
	if (*(philo->right_fork) == TAKEN && philo->right_fork_taken == 1)
		*(philo->right_fork) = AVAILABLE;
	pthread_mutex_unlock(philo->rfork_mut);
	pthread_mutex_lock(&philo->lfork_mut);
	if (philo->left_fork == TAKEN && philo->left_fork_taken == 1)
		philo->left_fork = AVAILABLE;
	pthread_mutex_unlock(&philo->lfork_mut);
	philo->right_fork_taken = 0;
	philo->left_fork_taken = 0;
	return (1);
}
