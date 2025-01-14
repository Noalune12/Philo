#include "philo.h"

void	init_struct(t_simulation *simu, int argc, char **argv, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		simu->philo[i].id = i + 1;
		simu->philo[i].status = 0; // 0 = thinking, 1 = eating, 2 = sleeping
		simu->philo[i].meals_eaten = 0;
		simu->philo[i].nb_philos = ft_atoi(argv[1]);
		simu->philo[i].die_time = ft_atoi(argv[2]);
		simu->philo[i].eat_time = ft_atoi(argv[3]);
		simu->philo[i].sleep_time = ft_atoi(argv[4]);
		if (argc == 6)
			simu->philo[i].nb_eat_times = ft_atoi(argv[5]);
		else
			simu->philo[i].nb_eat_times = -1;
		simu->philo[i].last_eaten = 0;
		simu->philo[i].dead = &simu->dead;
		simu->philo[i].left_fork = &forks[i];
		if (i == 0) // init mutexes
			simu->philo[i].right_fork = &forks[simu->philo[i].nb_philos - 1];
		else
			simu->philo[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	init_simulation(t_simulation *simu, t_philo *philo)
{
	simu->dead = 0;
	simu->philo = philo;
}

void	print_struct(t_philo *philo, int nb_philo)
{
	int i = 0;
	while (i < nb_philo)
	{
		printf("philo[%d].id = %d\n", i, philo[i].id);
		printf("philo[%d].status = %d\n", i, philo[i].status);
		printf("philo[%d].meals_eaten = %d\n", i, philo[i].meals_eaten);
		printf("philo[%d].nb_philos = %d\n", i, philo[i].nb_philos);
		printf("philo[%d].die_time = %zu\n", i, philo[i].die_time);
		printf("philo[%d].eat_time = %zu\n", i, philo[i].eat_time);
		printf("philo[%d].sleep_time = %zu\n", i, philo[i].sleep_time);
		printf("philo[%d].nb_eat_times = %d\n", i, philo[i].nb_eat_times);
		printf("philo[%d].last_eaten = %zu\n", i, philo[i].last_eaten);
		printf("philo[%d].dead = %p\n", i, philo[i].dead);
		printf("philo[%d].right_fork = %p\n", i, philo[i].right_fork);
		printf("philo[%d].left_fork = %p\n", i, philo[i].left_fork);
		printf("\n");
		i++;
	}
}
