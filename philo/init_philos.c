#include "philo.h"

static int	init_fork_mutex(char **argv, t_simulation *simu)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		if (pthread_mutex_init(&simu->philo[i].lfork_mut, NULL) != 0)
		{
			printf("Failed to initialize mutex\n");
			return (destroy_mutex(simu, 4, i));
		}
		i++;
	}
	return (0);
}

static void	init_info_philo(t_philo *philo, int argc, char **argv)
{
	philo->nb_philos = ft_atoi(argv[1]);
	philo->die_time = ft_atoi(argv[2]);
	philo->eat_time = ft_atoi(argv[3]);
	philo->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nb_eat_times = ft_atoi(argv[5]);
	else
		philo->nb_eat_times = -1;
	philo->start_time = get_current_time();
	philo->last_eaten = philo->start_time;
}

static void	add_forks_mutex(t_simulation *simu, int i)
{
	if (i == 0)
	{
		simu->philo[i].rfork_mut = &simu->philo[simu->nb_philos - 1].lfork_mut;
		simu->philo[i].right_fork = &simu->philo[simu->nb_philos - 1].left_fork;
	}
	else
	{
		simu->philo[i].rfork_mut = &simu->philo[i - 1].lfork_mut;
		simu->philo[i].right_fork = &simu->philo[i - 1].left_fork;
	}
	simu->philo[i].dead_mutex = &simu->dead_mutex;
	simu->philo[i].msg_mutex = &simu->msg_mutex;
	simu->philo[i].meal_mutex = &simu->meal_mutex;
	simu->philo[i].thread_mutex = &simu->thread_mutex;
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
		simu->philo[i].thread_fail = &simu->thread_fail;
		init_info_philo(&simu->philo[i], argc, argv);
		simu->philo[i].dead = &simu->dead;
		add_forks_mutex(simu, i);
		i++;
	}
	return (0);
}
