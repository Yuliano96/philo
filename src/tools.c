/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:39:21 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/18 23:19:26 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Devuelve el tiempo actual en milisegundos desde la época.
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// Imprime el estado actual de un filósofo si nadie ha muerto.
void	print_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->data->someone_died_mutex);
	if (!philo->data->someone_died)
	{
		pthread_mutex_lock(philo->data->write_mutex);
		printf("[%7lld ms] Philosopher %d %s\n", \
			get_time() - philo->data->start_time, philo->id, str);
		pthread_mutex_unlock(philo->data->write_mutex);
	}
	pthread_mutex_unlock(philo->data->someone_died_mutex);
}

// Destruye todos los mutex de los tenedores.
void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

// Destruye y libera un mutex dado.
void	destroy_mutex(pthread_mutex_t **mutex)
{
	if (*mutex)
	{
		pthread_mutex_destroy(*mutex);
		free(*mutex);
		*mutex = NULL;
	}
}

// Libera toda la memoria y recursos asociados a la estructura de datos principal.
void	free_data(t_data **data)
{
	if (*data)
	{
		if ((*data)->forks)
		{
			destroy_forks(*data);
			free((*data)->forks);
		}
		destroy_mutex(&(*data)->write_mutex);
		destroy_mutex(&(*data)->death_mutex);
		destroy_mutex(&(*data)->someone_died_mutex);
		if ((*data)->philo)
			free((*data)->philo);
		free(*data);
		*data = NULL;
	}
}
