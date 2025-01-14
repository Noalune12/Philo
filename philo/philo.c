#include "philo.h"

int	check_arg_content(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < 5)
	{
		if (ft_atoi(argv[i]) <= 0 || check_arg_content(argv[i]) == 0)
			return (0);
	}
	if (argc == 6 && (ft_atoi(argv[i]) < 0 || check_arg_content(argv[i]) == 0))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		philo[NB_MAX_PHILO];
	t_simulation	simu;
	pthread_mutex_t	forks[NB_MAX_PHILO];

	if ((argc != 6 && argc != 5) || check_args(argc, argv) == 0)
		return(write(1, "Invalid arguments", 17));
	else
	{
		init_simulation(&simu, philo);
		init_struct(&simu, argc, argv, forks);
		// print_struct(philo, ft_atoi(argv[1]));
		if (create_threads(&simu) == 1)
			return (1);
	}
	return (0);
}
