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

static void	think_eat_sleep(t_philo *philo)
{
	while (check_dead(philo) == 1)
	{
		if (eat_philo(philo) == 0)
			break ;
		if (philo->nb_eat_times != -1
			&& philo->meals_eaten == philo->nb_eat_times)
			break ;
		sleep_philo(philo);
		think_philo(philo);
	}
}

void	*philo_routine(void *ptr)
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
	if (philo->id % 2 == 0)
	{
		think_philo(philo);
		ft_usleep(philo->eat_time / 2, philo);
	}
	think_eat_sleep(philo);
	return (NULL);
}

void	*one_philo_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	think_philo(philo);
	pthread_mutex_lock(&philo->lfork_mut);
	print_msg("has taken a fork", philo, philo->id);
	ft_usleep(philo->die_time, philo);
	pthread_mutex_unlock(&philo->lfork_mut);
	print_msg("is dead", philo, philo->id);
	return (NULL);
}
