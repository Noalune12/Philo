#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->dead_mutex);
	return (1);
}

// check all eaten

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (check_dead(philo) == 1)
	{
		think_philo(philo);

		// Take forks
		pthread_mutex_lock(philo->left_fork);
		print_msg("has taken a fork", philo, philo->id);
		if (philo->nb_philos == 1)
		{
			// usleep(philo->die_time * 1000);
			pthread_mutex_unlock(philo->left_fork);
			break;
		}
		pthread_mutex_lock(philo->right_fork);
		print_msg("has taken a fork", philo, philo->id);

		// Eating
		philo->status = 1;
		philo->last_eaten = get_current_time();
		print_msg("is eating", philo, philo->id);
		usleep(philo->eat_time * 1000);
		philo->meals_eaten++;

		// Release forks
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// Sleeping
		philo->status = 2;
		print_msg("is sleeping", philo, philo->id);
		usleep(philo->sleep_time * 1000);
	}
	return (NULL);
}

int	create_threads(t_simulation *simu)
{
	int	i;
	pthread_t monitor_thread;

	pthread_create(&monitor_thread, NULL, monitor_philo, simu->philo); // protect
	i = 0;
	while (i < simu->philo[0].nb_philos)
	{
		if (pthread_create(&simu->philo[i].thread, NULL, &philo_routine, &simu->philo[i]) != 0)
			return (1); // "thread creation failed"
		i++;
	}
	pthread_join(monitor_thread, NULL); //protect
	i = 0;
	while (i < simu->philo[0].nb_philos)
	{
		if (pthread_join(simu->philo[i].thread, NULL) != 0)
			return (1); // "thread join failed"
		i++;
	}
	return (0);
}
