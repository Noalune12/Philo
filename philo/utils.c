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
	int mutex_forks) //pthread_mutex_t *forks,
{
	int	i;
	(void)mutex_forks;
	i = 0;
	//need protection ??
	if (mutex_simu >= 1)
		pthread_mutex_destroy(&simu->msg_mutex);
	if (mutex_simu >= 2)
		pthread_mutex_destroy(&simu->meal_mutex);
	if (mutex_simu >= 3)
		pthread_mutex_destroy(&simu->dead_mutex);
	// if (mutex_forks >= 0)
	// {
	// 	while (i < simu->philo[0].nb_philos && i < mutex_forks)
	// 	{
	// 		pthread_mutex_destroy(&forks[i]);
	// 		i++;
	// 	}
	// }
	return (1);
}

int	error_msg(char *str)
{
	printf("%s", str);
	return (1);
}
