#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_simualtion
{
	size_t	nb_philo;
	size_t	die_time;
	size_t	eat_time;
	size_t	sleep_time;
	size_t	eat_times;
}	t_simulation;

typedef struct s_philosophers
{
	size_t	id;
	int	status;
	int	last_eaten;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex;
}	t_philosophers;

int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);

#endif
