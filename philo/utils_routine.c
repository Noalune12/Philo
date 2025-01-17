#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_msg(char *str, t_philo *philo, int id)
{
	size_t	time;

	// pthread_mutex_lock(philo->dead_mutex);
	pthread_mutex_lock(philo->msg_mutex);
	time = get_current_time() - philo->start_time;
	// printf("sphilo death = %d\n\n", *philo->dead);
	if (*philo->dead == 0)
		printf("%zu %d %s\n", time, id, str);
	// pthread_mutex_unlock(philo->dead_mutex);
	pthread_mutex_unlock(philo->msg_mutex);
}

void	think_philo(t_philo *philo)
{
	philo->status = 0; // not needed
	print_msg("is thinking", philo, philo->id);
}

void	sleep_philo(t_philo *philo)
{
	philo->status = 2;
	print_msg("is sleeping", philo, philo->id);
	usleep(philo->sleep_time * 1000);
}

int	eat_philo(t_philo *philo)
{
	// Take forks
	pthread_mutex_lock(philo->left_fork);
	print_msg("has taken a fork", philo, philo->id);
	if (philo->nb_philos == 1)
	{
		usleep(philo->die_time * 1000);
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	pthread_mutex_lock(philo->right_fork);
	print_msg("has taken a fork", philo, philo->id);
	// Eating
	philo->status = 1;
	philo->last_eaten = get_current_time();
	print_msg("is eating", philo, philo->id);
	usleep(philo->eat_time * 1000);
	pthread_mutex_lock(philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_mutex);
	// Release forks
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}
