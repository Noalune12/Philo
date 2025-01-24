#include "philo.h"

static int	check_arg_content(char *str)
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

static int	check_args(int argc, char **argv)
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
	t_philo			philo[NB_MAX_PHILO];
	t_simulation	simu;

	if ((argc != 6 && argc != 5) || check_args(argc, argv) == 0)
	{
		printf("Invalid arguments");
		return (1);
	}
	else
	{
		memset((void *)philo, 0, sizeof(philo));
		if (init_simulation(&simu, philo, argv) == 1
			|| init_struct(&simu, argc, argv) == 1)
			return (1);
		// print_struct(philo, ft_atoi(argv[1]));
		if (create_threads(&simu) == 1)
			return (destroy_mutex(&simu, 4, ft_atoi(argv[1])));
	}
	destroy_mutex(&simu, 4, ft_atoi(argv[1]));
	return (0);
}
