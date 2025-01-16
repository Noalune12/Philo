#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <pthread.h>
# include <stdio.h>
#include <sys/time.h>

# define NB_MAX_PHILO 200

typedef struct s_philo
{
	pthread_t	thread;
	int				id;
	int				status; // 0 = thinking, 1 = eating, 2 = sleeping
	int				meals_eaten;
	int				nb_philos;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			start_time;
	int				nb_eat_times;
	size_t			last_eaten;
	int				*dead;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*msg_mutex;
	pthread_mutex_t	*meal_mutex;
}	t_philo;

typedef struct s_simualtion
{
	int	dead;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	dead_mutex;
	t_philo	*philo;
}	t_simulation;

int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);
int	init_simulation(t_simulation *simu, t_philo *philo);
int	init_struct(t_simulation *simu, int argc, char **argv, pthread_mutex_t *forks);
int	create_threads(t_simulation *simu);
size_t	get_current_time(void);
void	print_msg(char *str, t_philo *philo, int id);
int	error_msg(char *str);

void	*monitor_philo(void *ptr);
void	think_philo(t_philo *philo);
void	sleep_philo(t_philo *philo);
int		eat_philo(t_philo *philo);

int	destroy_mutex(t_simulation *simu, pthread_mutex_t *forks, int mutex_simu, int mutex_forks);
void	print_struct(t_philo *philo, int nb_philo);

#endif
