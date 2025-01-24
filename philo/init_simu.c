#include "philo.h"

static int	init_mutex_simu(t_simulation *simu)
{
	if (pthread_mutex_init(&simu->msg_mutex, NULL) != 0)
		return (destroy_mutex(simu, 0, -1));
	if (pthread_mutex_init(&simu->meal_mutex, NULL) != 0)
		return (destroy_mutex(simu, 1, -1));
	if (pthread_mutex_init(&simu->dead_mutex, NULL) != 0)
		return (destroy_mutex(simu, 2, -1));
	// if (pthread_mutex_init(&simu->thread_mutex, NULL) != 0)
		// return (destroy_mutex(simu, 3, -1));
	return (0);
}

int	init_simulation(t_simulation *simu, t_philo *philo, char **argv)
{
	simu->dead = 0;
	simu->thread_fail = -1;
	simu->nb_philos = ft_atoi(argv[1]);
	if (init_mutex_simu(simu) == 1)
	{
		printf("Failed to initialize mutex\n");
		return (1);
	}
	simu->philo = philo;
	return (0);
}

// delete
void	print_struct(t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		printf("philo[%d].id = %d\n", i, philo[i].id);
		// printf("philo[%d].status = %d\n", i, philo[i].status);
		// printf("philo[%d].meals_eaten = %d\n", i, philo[i].meals_eaten);
		// printf("philo[%d].nb_philos = %d\n", i, philo[i].nb_philos);
		// printf("philo[%d].die_time = %zu\n", i, philo[i].die_time);
		// printf("philo[%d].eat_time = %zu\n", i, philo[i].eat_time);
		// printf("philo[%d].sleep_time = %zu\n", i, philo[i].sleep_time);
		// printf("philo[%d].start_time = %zu\n", i, philo[i].start_time);
		// printf("philo[%d].nb_eat_times = %d\n", i, philo[i].nb_eat_times);
		// printf("philo[%d].last_eaten = %zu\n", i, philo[i].last_eaten);
		// printf("philo[%d].dead = %p\n", i, philo[i].dead);
		printf("philo[%d].right_fork_mutex = %p\n", i, philo[i].rfork_mut);
		printf("philo[%d].left_fork_mutex = %p\n", i, &philo[i].lfork_mut);
		printf("philo[%d].right_fork = %d // %p\n", i, (*philo[i].right_fork), philo[i].right_fork);
		printf("philo[%d].left_fork = %d // %p\n", i, philo[i].left_fork,  &philo[i].left_fork);
		if (i > nb_philo && i < nb_philo)
		{
			if (&philo[i + 1].lfork_mut == philo[i].rfork_mut)
				printf("FORK MUTEX OK\n");
		}
		// printf("philo[%d].left_fork = %d\n", i, *(philo[i].left_fork));
		printf("\n");
		i++;
	}
}
