/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:41:28 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/27 09:44:52 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

static t_philo	*alloc_philo(t_philo *philo, char **argv)
{
	philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
	if (!philo)
		return (NULL);
	return (philo);
}

int	main(int argc, char **argv)
{
	t_simulation	simu;
	t_philo			*philo;

	philo = NULL;
	if ((argc != 6 && argc != 5) || check_args(argc, argv) == 0)
	{
		printf("Invalid arguments");
		return (1);
	}
	else
	{
		philo = alloc_philo(philo, argv);
		if (!philo)
			return (error_msg("Malloc failed", &simu));
		memset((void *)philo, 0, ft_atoi(argv[1]) * sizeof(t_philo));
		if (init_simulation(&simu, philo, argv) == 1
			|| init_struct(&simu, argc, argv) == 1)
			return (1);
		if (create_threads(&simu) == 1)
			return (destroy_mutex(&simu, 4, ft_atoi(argv[1])));
	}
	destroy_mutex(&simu, 4, ft_atoi(argv[1]));
	return (0);
}
