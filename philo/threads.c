#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->dead_mutex);
		exit(EXIT_SUCCESS);
	}
	pthread_mutex_unlock(philo->dead_mutex);
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;

	while (*(philo->dead) == 0)
	{
		// Check if one philo has died
		pthread_mutex_lock(philo->dead_mutex);
		if (*(philo->dead) == 1)
		{
			pthread_mutex_unlock(philo->dead_mutex);
			break;
		}
		pthread_mutex_unlock(philo->dead_mutex);

		// Thinking
		philo->status = 0;
		printf("Philo %d is thinking\n", philo->id);
		check_dead(philo);

		// Take forks -  they all take the left fork
		pthread_mutex_lock(philo->left_fork);
		printf("Philo %d has taken the left fork\n", philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("Philo %d has taken the right fork\n", philo->id);
		check_dead(philo);

		// Eating
		philo->status = 1;
		philo->last_eaten = get_current_time();
		printf("Philo %d is eating\n", philo->id);
		usleep(philo->eat_time * 1000);
		philo->meals_eaten++;
		check_dead(philo);

		// Release forks
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// Sleeping
		philo->status = 2;
		printf("Philo %d is sleeping\n", philo->id);
		usleep(philo->sleep_time * 1000);
		check_dead(philo);

		// Check if philo died due to time since last meal
		pthread_mutex_lock(philo->dead_mutex);
		if (get_current_time() - philo->last_eaten > philo->die_time)
		{
			*(philo->dead) = 1;
			printf("Philo %d has died\n", philo->id);
		}
		pthread_mutex_unlock(philo->dead_mutex);
	}
	return (NULL);
}

int	create_threads(t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < simu->philo[0].nb_philos)
	{
		if (pthread_create(&simu->philo[i].thread, NULL, &philo_routine, &simu->philo[i]) != 0)
			return (1); // "thread creation failed"
		i++;
	}
	i = 0;
	while (i < simu->philo[0].nb_philos)
	{
		if (pthread_join(simu->philo[i].thread, NULL) != 0)
			return (1); // "thread join failed"
		i++;
	}
	return (0);
}
