/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:31:08 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/22 22:51:28 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Reserva memoria para la estructura principal de datos
int	allocate_data(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (0);
	return (1);
}

// Inicializa los argumentos recibidos por línea de comandos en la estructura de datos
int	init_arguments(t_data *data, char **argv, int argc)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->someone_died = 0;
	data->all_ate = 0;
	if (argc == 6)
		data->meals_required = ft_atoi(argv[5]);
	else
		data->meals_required = 0;
	return (1);
}

// Inicializa todos los recursos necesarios (memoria y mutex)
int	initialize_resources(t_data **data)
{
	if (!memory_initialization(data))
		return (0);
	if (!mutex_init_forks(data))
		return (0);
	if (pthread_mutex_init((*data)->write_mutex, NULL) != 0
		|| pthread_mutex_init((*data)->death_mutex, NULL) != 0
		|| pthread_mutex_init((*data)->someone_died_mutex, NULL) != 0)
		return (0);
	return (1);
}

// Inicializa toda la estructura de datos principal y recursos asociados
int	data_init(t_data **data, char **argv, int argc)
{
	if (!allocate_data(data))
		return (0);
	if (!init_arguments(*data, argv, argc))
		return (0);
	if (!initialize_resources(data))
	{
		free_data(data);
		return (0);
	}
	if (!philo_init(*data))
	{
		free_data(data);
		return (0);
	}
	return (1);
}

// Inicializa la estructura de cada filósofo y crea los hilos necesarios
int	philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].right_fork = &data->forks[i];
		data->philo[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		data->philo[i].data = data;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal_time = get_time();
		i++;
	}
	data->start_time = get_time();
	if (!create_threads(data->philo))
		return (0);
	if (pthread_create(&data->death_monitor, NULL, death_monitor, data) != 0)
		return (0);
	if (data->meals_required > 0)
		if (pthread_create(&data->meals_monitor, NULL, \
			meals_monitor, data) != 0)
			return (0);
	return (1);
}
