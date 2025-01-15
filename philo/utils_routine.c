#include "philo.h"

void	print_msg(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->msg_mutex);
	time = get_current_time() - philo->start_time;
	if (*philo->dead == 0)
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->msg_mutex);
}
