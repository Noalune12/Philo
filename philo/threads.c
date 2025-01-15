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

void *monitor_philo(void *ptr)
{
	t_philo *philo = (t_philo *)ptr;

	while (1)
	{
		usleep(1000); // Check every 1 millisecond
		pthread_mutex_lock(philo->dead_mutex);
		if (*(philo->dead) == 1)
		{
			pthread_mutex_unlock(philo->dead_mutex);
			break;
		}
		if (get_current_time() - philo->last_eaten > philo->die_time)
		{
			*(philo->dead) = 1;
			size_t time = get_current_time() - philo->start_time;
			printf("%zu %d died\n", time, philo->id);
			pthread_mutex_unlock(philo->dead_mutex);
			break;
		}
		pthread_mutex_unlock(philo->dead_mutex);
	}
	return NULL;
}

void	*philo_routine(void *ptr)
{
	t_philo	*philo;
	size_t	time;
	pthread_t monitor_thread;

	philo = (t_philo *)ptr;

	pthread_create(&monitor_thread, NULL, monitor_philo, philo); // protect
	if (philo->id % 2 == 0)
		usleep(1);
	while (check_dead(philo) == 1)
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
		print_msg("is thinking", philo, philo->id);
		if (check_dead(philo) == 0)
			break;

		// check in the background until can eat if time to die is done

		// Take forks -  they all take the left fork
		pthread_mutex_lock(philo->left_fork);
		print_msg("has taken a fork", philo, philo->id);
		if (check_dead(philo) == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			break;
		}
		if (philo->nb_philos == 1)
		{
			usleep(philo->die_time * 1000);
			pthread_mutex_unlock(philo->left_fork);
			*(philo->dead) = 1;
			time = get_current_time() - philo->start_time;
			printf("%zu %d died\n", time, philo->id);
			break;
		}
		pthread_mutex_lock(philo->right_fork);
		print_msg("has taken a fork", philo, philo->id);
		if (check_dead(philo) == 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			break;
		}

		// Eating
		philo->status = 1;
		philo->last_eaten = get_current_time();
		print_msg("is eating", philo, philo->id);
		usleep(philo->eat_time * 1000);
		philo->meals_eaten++;
		if (check_dead(philo) == 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
			break;
		}

		// Release forks
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		// Sleeping
		philo->status = 2;
		print_msg("is sleeping", philo, philo->id);
		usleep(philo->sleep_time * 1000);
		if (check_dead(philo) == 0)
			break;

		// Check if philo died due to time since last meal
		pthread_mutex_lock(philo->dead_mutex);
		if (get_current_time() - philo->last_eaten > philo->die_time)
		{
			*(philo->dead) = 1;
			time = get_current_time() - philo->start_time;
			printf("%zu %d died\n", time, philo->id);
		}
		pthread_mutex_unlock(philo->dead_mutex);
	}
	pthread_join(monitor_thread, NULL); //protect
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
