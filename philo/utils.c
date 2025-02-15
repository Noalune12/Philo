/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:41:39 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/27 09:44:17 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_checknptr(long long nb, int sign, size_t i, const char *nptr)
{
	if ((long)nb > (LONG_MAX - (nptr[i] + '0')) / 10)
	{
		if (sign == -1)
			return (0);
		else if (sign == 1)
			return (-1);
	}
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int				sign;
	long long		res;
	size_t			i;

	sign = 1;
	res = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (ft_checknptr(res, sign, i, nptr) == 0)
			return (0);
		else if (ft_checknptr(res, sign, i, nptr) == -1)
			return (-1);
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return ((int)(res * sign));
}

int	destroy_mutex(t_simulation *simu, int mutex_simu,
	int mutex_forks)
{
	int	i;

	i = 0;
	if (mutex_simu >= 1)
		pthread_mutex_destroy(&simu->msg_mutex);
	if (mutex_simu >= 2)
		pthread_mutex_destroy(&simu->meal_mutex);
	if (mutex_simu >= 3)
		pthread_mutex_destroy(&simu->dead_mutex);
	if (mutex_simu >= 4)
		pthread_mutex_destroy(&simu->thread_mutex);
	if (mutex_forks >= 0)
	{
		while (i < simu->philo[0].nb_philos && i < mutex_forks)
		{
			pthread_mutex_destroy(&simu->philo[i].lfork_mut);
			i++;
		}
	}
	free(simu->philo);
	return (1);
}

int	error_msg(char *str, t_simulation *simu)
{
	pthread_mutex_lock(&simu->msg_mutex);
	printf("%s", str);
	pthread_mutex_unlock(&simu->msg_mutex);
	return (1);
}
