/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meals_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:47:23 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/24 14:52:35 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * ft_usleep - Duerme durante el tiempo especificado en milisegundos,
 * comprobando periódicamente si alguien ha muerto.
 * @time_in_ms: Tiempo a dormir en milisegundos.
 * @philo: Puntero a la estructura del filósofo.
 */
void	ft_usleep(size_t time_in_ms, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < time_in_ms)
	{
		usleep(250);
		pthread_mutex_lock(philo->data->someone_died_mutex);
		if (philo->data->someone_died)
		{
			pthread_mutex_unlock(philo->data->someone_died_mutex);
			break ;
		}
		pthread_mutex_unlock(philo->data->someone_died_mutex);
	}
}

/**
 * think - Hace que el filósofo piense durante un breve periodo.
 * @philo: Puntero a la estructura del filósofo.
 */
void	think(t_philo *philo)
{
	print_state(philo, "is thinking");
}

/**
 * some_died - Verifica si algún filósofo ha muerto.
 * @philo: Puntero a la estructura del filósofo.
 *
 * Retorna 1 si alguien ha muerto, 0 en caso contrario.
 */
int	some_died(t_philo *philo)
{
	pthread_mutex_lock(philo->data->someone_died_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(philo->data->someone_died_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->data->someone_died_mutex);
	return (0);
}

// Función auxiliar para saber si todos han comido lo requerido
int	all_philos_ate(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(data->death_mutex);
		if (data->philo[i].meals_eaten < data->meals_required)
		{
			pthread_mutex_unlock(data->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(data->death_mutex);
		i++;
	}
	return (1);
}

/**
 * @brief Monitorea el estado de las comidas de los filósofos.
 *
 * Esta función se ejecuta en un hilo separado y verifica continuamente si algún filósofo ha muerto
 * o si todos los filósofos han comido la cantidad requerida de veces. Si alguno muere, termina el monitoreo.
 * Si todos han comido, actualiza la variable 'all_ate' y finaliza la función.
 *
 * @param arg Puntero a la estructura de datos principal (t_data).
 * @return NULL al finalizar el monitoreo.
 */
void	*meals_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (some_died(data->philo))
			break ;
		if (all_philos_ate(data))
		{
			pthread_mutex_lock(data->death_mutex);
			data->all_ate = 1;
			pthread_mutex_unlock(data->death_mutex);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
