#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long usec)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	gettimeofday(&current, NULL);
	while ((current.tv_sec - start.tv_sec) * 1000000 + (current.tv_usec - start.tv_usec) < usec)
	{
		usleep(100);
		gettimeofday(&current, NULL);
	}
}

void	print_msg(char *str, t_philo *philo, int id)
{
	size_t	time;

	// pthread_mutex_lock(philo->dead_mutex);
	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->msg_mutex);
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
	usleep(10);
}

void	sleep_philo(t_philo *philo)
{
	philo->status = 2;
	print_msg("is sleeping", philo, philo->id);
	ft_usleep(philo->sleep_time * 1000);
}
