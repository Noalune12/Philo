#include "philo.h"

int	check_all_meals_eaten(t_philo *philo)
{
	int	i;
	int	done_eating;

	// printf("nb eat times = %d\n\n", philo[0].nb_eat_times);
	if (philo[0].nb_eat_times == -1)
		return (0);
	i = 0;
	done_eating = 0;
	while (i < philo[0].nb_philos)
	{
		pthread_mutex_lock(philo[i].meal_mutex);
		if (philo[i].meals_eaten >= philo[i].nb_eat_times)
			done_eating++;
		pthread_mutex_unlock(philo[i].meal_mutex);
		i++;
	}
	if (done_eating == philo[0].nb_philos)
	{
		pthread_mutex_lock(philo[0].dead_mutex);
		*philo->dead = -1;
		pthread_mutex_unlock(philo[0].dead_mutex);
		return (1);
	}
	return (0);
}

static int	check_dead_philo(t_philo *philo)
{
	size_t	time;

	if (get_current_time() - philo->last_eaten >= philo->die_time
		&& philo->status != 1)
	{
		pthread_mutex_lock(philo->dead_mutex);
		*(philo->dead) = 1;
		pthread_mutex_unlock(philo->dead_mutex);
		pthread_mutex_lock(philo->msg_mutex);
		time = get_current_time() - philo->start_time;
		printf(RED"%zu %d died\n"RESET, time, philo->id);
		pthread_mutex_unlock(philo->msg_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_philo(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)ptr;
	// check if all thread laund = 1;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(philo->dead_mutex);
		if (*(philo->dead) == 1 || *(philo->dead) == -1)
		{
			pthread_mutex_unlock(philo->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->dead_mutex);
		while (i < philo[0].nb_philos)
		{
			if (check_dead_philo(&philo[i]) == 1)
				break ;
			i++;
		}
		if (check_all_meals_eaten(philo) == 1)
			break ;
	}
	return (NULL);
}
