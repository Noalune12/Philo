#include "philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*(philo->dead) == 1 || *(philo->dead) == -1)
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
		usleep(100);
	while (check_dead(philo) == 1)
	{
		//check dead inside loop to close program earlier ?
		// printf("dead = %d\n\n", *(philo->dead));
		think_philo(philo);
		if (eat_philo(philo) == 0)
			break ;
		sleep_philo(philo);
	}
	return (NULL);
}

int	create_threads(t_simulation *simu)
{
	int	i;
	pthread_t monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor_philo, simu->philo) != 0)
		return (error_msg("Thread creation failed\n"));
	i = 0;
	while (i < simu->philo[0].nb_philos)
	{
		if (pthread_create(&simu->philo[i].thread, NULL, &philo_routine, &simu->philo[i]) != 0)
			return (error_msg("Thread creation failed\n"));
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (error_msg("Thread join failed\n"));
	i = 0;
	while (i < simu->philo[0].nb_philos)
	{
		if (pthread_join(simu->philo[i].thread, NULL) != 0)
			return (error_msg("Thread join failed\n"));
		i++;
	}
	return (0);
}
