#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(size_t ms, t_philo *philo)
{
	size_t	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < ms && check_dead(philo) == 1)
		usleep(500);
}

void	print_msg(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->msg_mutex);
	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->dead_mutex);
	if (*philo->dead == 0)
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->dead_mutex);
	pthread_mutex_unlock(philo->msg_mutex);
}

void	think_philo(t_philo *philo)
{
	print_msg(BLUE"is thinking"RESET, philo, philo->id);
	usleep(10);
}

void	sleep_philo(t_philo *philo)
{
	print_msg(PURPLE"is sleeping"RESET, philo, philo->id);
	ft_usleep(philo->sleep_time, philo);
}
