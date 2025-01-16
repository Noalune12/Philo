#include "philo.h"

static int	check_dead_philo(t_philo *philo)
{
	size_t	time;

	if (get_current_time() - philo->last_eaten >= philo->die_time)
	{
		*(philo->dead) = 1;
		// pthread_mutex_lock(philo->msg_mutex);
		time = get_current_time() - philo->start_time;
		printf("%zu %d died\n", time, philo->id);
		// pthread_mutex_unlock(philo->msg_mutex);
		// pthread_mutex_unlock(philo->dead_mutex);
		return (1);
	}
	return (0);
}

void *monitor_philo(void *ptr)
{
	t_philo *philo;
	int	i;

	philo = (t_philo *)ptr;
	while (1)
	{
		i = 0;
		// pthread_mutex_lock(philo->dead_mutex);
		if (*(philo->dead) == 1)
		{
			// pthread_mutex_unlock(philo->dead_mutex);
			break;
		}
		while (i < philo[0].nb_philos)
		{
			if (check_dead_philo(&philo[i]) == 1)
				break;
			i++;
		}
		// pthread_mutex_unlock(philo->dead_mutex);
	}
	return NULL;
}
