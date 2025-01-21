#include "philo.h"

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
