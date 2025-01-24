#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <sys/time.h>

# define NB_MAX_PHILO 200
# define AVAILABLE 0
# define TAKEN 1
# define CREATION -1
# define FAIL 1
# define SUCCESS 0

# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define RESET   "\033[0m"
# define PURPLE "\033[0;35m"

typedef struct s_philo
{
	pthread_t		thread;
	int				*thread_fail;
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
	int				*right_fork;
	int				left_fork;
	int				right_fork_taken;
	int				left_fork_taken;
	pthread_mutex_t	*rfork_mut;
	pthread_mutex_t	lfork_mut;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*msg_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*status_mutex;
	pthread_mutex_t	*thread_mutex;
}	t_philo;

typedef struct s_simualtion
{
	int				dead;
	int				thread_fail;
	int				nb_philos;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	thread_mutex;
	t_philo			*philo;
}	t_simulation;

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
int		init_simulation(t_simulation *simu, t_philo *philo, char **argv);
int		init_struct(t_simulation *simu, int argc, char **argv,
			pthread_mutex_t *forks);
int		error_msg(char *str, t_simulation *simu);

int		create_threads(t_simulation *simu);
size_t	get_current_time(void);
void	print_msg(char *str, t_philo *philo, int id);
int		check_dead(t_philo *philo);
void	*monitor_philo(void *ptr);
void	*one_philo_routine(void *ptr);
void	*philo_routine(void *ptr);
void	think_philo(t_philo *philo);
void	sleep_philo(t_philo *philo);
int		eat_philo(t_philo *philo);
void	ft_usleep(long usec, t_philo *philo);

int		destroy_mutex(t_simulation *simu,
			int mutex_simu, int mutex_forks);

void	print_struct(t_philo *philo, int nb_philo);

#endif
