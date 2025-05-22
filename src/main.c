/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:18:50 by ypacileo          #+#    #+#             */
/*   Updated: 2025/05/22 22:46:31 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	size_t	i;
	long	number;
	int		sign;

	i = 0;
	sign = 1;
	number = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == '\f' )
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		number = number * 10 + s[i] - 48;
		i++;
	}
	return (number * sign);
}

int	is_positive_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		if (!is_positive_number(argv[i]) || ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	long	start;

	if (!validate_args(argc, argv))
		return (write(2, "Error: invalid argument\n", 25), 1);
	if (ft_atoi(argv[1]) == 1)
	{
		start = get_time();
		printf("[%7ld ms] Philosopher 1 is thinking\n", get_time() - start);
		printf("[%7ld ms] Philosopher 1 has taken the left fork\n", \
			get_time() - start);
		usleep(ft_atoi(argv[2]) * 1000);
		printf("[%7ld ms] Philosopher 1 died\n", get_time() - start);
		return (0);
	}
	if (!data_init(&data, argv, argc))
		return (write(2, "Error: in initializing data\n", 29), 1);
	wait_thread(data->philo);
	pthread_join(data->death_monitor, NULL);
	if (data->meals_required > 0)
		pthread_join(data->meals_monitor, NULL);
	free_data(&data);
	return (0);
}
