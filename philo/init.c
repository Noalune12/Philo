#include "philo.h"

static int	init_fork_mutex(char **argv, t_simulation *simu) //pthread_mutex_t *forks,
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		// if (pthread_mutex_init(&forks[i], NULL) != 0)
		// {
		// 	printf("Failed to initialize mutex\n");
		// 	return (destroy_mutex(simu, forks, 3, i));
		// }
		// i++;
		if (pthread_mutex_init(&simu->philo[i].left_fork_mutex, NULL) != 0)
		{
			printf("Failed to initialize mutex\n");
			return (destroy_mutex(simu, 3, i)); //change
		}
		i++;
	}
	return (0);
}

static void	init_info_philo(t_philo *philo, int argc, char **argv)
{
	// philo->status = 0;
	// philo->meals_eaten = 0;
	philo->nb_philos = ft_atoi(argv[1]);
	philo->die_time = ft_atoi(argv[2]);
	philo->eat_time = ft_atoi(argv[3]);
	philo->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nb_eat_times = ft_atoi(argv[5]);
	else
		philo->nb_eat_times = -1;
	philo->start_time = get_current_time();
	philo->last_eaten = get_current_time();
}

static void	add_forks_mutex(t_simulation *simu, int i)
{
	// simu->philo[i].left_fork_mutex = &forks[i];
	if (i == 0)
	{
		simu->philo[i].right_fork_mutex = &simu->philo[simu->philo[i].nb_philos - 1].left_fork_mutex;
		simu->philo[i].right_fork = &simu->philo[simu->philo[i].nb_philos - 1].left_fork;
	}
	else
	{
		simu->philo[i].right_fork_mutex = &simu->philo[i - 1].left_fork_mutex;
		simu->philo[i].right_fork = &simu->philo[i - 1].left_fork;
	}
	simu->philo[i].dead_mutex = &simu->dead_mutex;
	simu->philo[i].msg_mutex = &simu->msg_mutex;
	simu->philo[i].meal_mutex = &simu->meal_mutex;
}

int	init_struct(t_simulation *simu, int argc, char **argv,
	pthread_mutex_t *forks)
{
	int	i;

	(void)forks;
	simu->philo[0].nb_philos = ft_atoi(argv[1]);
	if (init_fork_mutex(argv, simu) == 1)
		return (1);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		simu->philo[i].id = i + 1;
		init_info_philo(&simu->philo[i], argc, argv);
		simu->philo[i].dead = &simu->dead;
		add_forks_mutex(simu, i);
		i++;
	}
	return (0);
}

int	init_simulation(t_simulation *simu, t_philo *philo)
{
	simu->dead = 0;
	if (pthread_mutex_init(&simu->msg_mutex, NULL) != 0)
	{
		printf("Failed to initialize mutex\n");
		return (destroy_mutex(simu, 1, -1));
	}
	if (pthread_mutex_init(&simu->meal_mutex, NULL) != 0)
	{
		printf("Failed to initialize mutex\n");
		return (destroy_mutex(simu, 2, -1));
	}
	if (pthread_mutex_init(&simu->dead_mutex, NULL) != 0)
	{
		printf("Failed to initialize mutex\n");
		return (destroy_mutex(simu, 3, -1));
	}
	simu->philo = philo;
	return (0);
}

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
		printf("philo[%d].right_fork_mutex = %p\n", i, philo[i].right_fork_mutex);
		printf("philo[%d].left_fork_mutex = %p\n", i, &philo[i].left_fork_mutex);
		printf("philo[%d].right_fork = %d // %p\n", i, (*philo[i].right_fork), philo[i].right_fork);
		printf("philo[%d].left_fork = %d // %p\n", i, philo[i].left_fork,  &philo[i].left_fork);
		if (i > nb_philo && i < nb_philo)
		{
			if (&philo[i + 1].left_fork_mutex == philo[i].right_fork_mutex)
				printf("FORK MUTEX OK\n");
		}
		// printf("philo[%d].left_fork = %d\n", i, *(philo[i].left_fork));
		printf("\n");
		i++;
	}
}
