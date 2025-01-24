#include "philo.h"

static int	check_all_meals_eaten(t_philo *philo)
{
	int	i;
	int	done_eating;

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

	// pthread_mutex_lock(philo->status_mutex);
	pthread_mutex_lock(philo->meal_mutex);
	if (get_current_time() - philo->last_eaten >= philo->die_time
		&& philo->eating != 1)
	{
		// pthread_mutex_unlock(philo->status_mutex);
		pthread_mutex_unlock(philo->meal_mutex);
		pthread_mutex_lock(philo->dead_mutex);
		*(philo->dead) = 1;
		pthread_mutex_unlock(philo->dead_mutex);
		pthread_mutex_lock(philo->msg_mutex);
		time = get_current_time() - philo->start_time;
		printf(RED"%zu %d died\n"RESET, time, philo->id);
		pthread_mutex_unlock(philo->msg_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_mutex);
	// pthread_mutex_unlock(philo->status_mutex);
	return (0);
}

static void	monitor_loop(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo[0].nb_philos)
		{
			if (check_dead_philo(&philo[i]) == 1)
				return ;
			i++;
		}
		if (check_all_meals_eaten(philo) == 1)
			return ;
	}
}

void	*monitor_philo(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	// while (1)
	// {
	// 	pthread_mutex_lock(philo->thread_mutex);
	// 	if (*(philo->thread_fail) != CREATION)
	// 		break ;
	// 	pthread_mutex_unlock(philo->thread_mutex);
	// 	ft_usleep(10, philo);
	// }
	// pthread_mutex_unlock(philo->thread_mutex);
	// if (*(philo->thread_fail) == FAIL)
	// 	return (NULL);
	monitor_loop(philo);
	return (NULL);
}
