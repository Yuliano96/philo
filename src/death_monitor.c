/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:34:32 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/22 22:52:34 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * check_all_ate - Verifica si todos los filósofos han terminado de comer.
 * @data: Puntero a la estructura de datos compartida.
 *
 * Esta función bloquea el mutex death_mutex para leer de forma segura la
 * bandera all_ate, que indica si todos los filósofos han comido la cantidad
 * requerida de veces. Retorna 1 si todos han comido, 0 en caso contrario.
 */
int	check_all_ate(t_data *data)
{
	int	all_ate;

	pthread_mutex_lock(data->death_mutex);
	all_ate = data->all_ate;
	pthread_mutex_unlock(data->death_mutex);
	return (all_ate);
}

/**
 * get_dead_philo - Busca si algún filósofo ha muerto.
 * @data: Puntero a la estructura de datos compartida.
 *
 * Recorre todos los filósofos y verifica si alguno ha excedido el tiempo máximo sin comer.
 * Retorna el índice del filósofo muerto o -1 si ninguno ha muerto.
 */
int	get_dead_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(data->death_mutex);
		if ((get_time() - data->philo[i].last_meal_time) > data->time_to_die)
		{
			pthread_mutex_unlock(data->death_mutex);
			return (i);
		}
		pthread_mutex_unlock(data->death_mutex);
		i++;
	}
	return (-1);
}

/**
 * handle_philo_death - Maneja el evento de la muerte de un filósofo.
 * @data: Puntero a la estructura de datos compartida.
 * @dead_idx: Índice del filósofo que murió.
 *
 * Esta función establece la bandera someone_died de manera segura usando
 * mutex, luego imprime un mensaje indicando qué filósofo murió y en qué
 * momento. Se usan mutex para asegurar el acceso seguro a los datos
 * compartidos y sincronizar la salida por consola.
 */
void	handle_philo_death(t_data *data, int dead_idx)
{
	pthread_mutex_lock(data->someone_died_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(data->someone_died_mutex);
	pthread_mutex_lock(data->write_mutex);
	printf("[%7lld ms] El filósofo %d murió\n", \
		get_time() - data->start_time, data->philo[dead_idx].id);
	pthread_mutex_unlock(data->write_mutex);
}

/**
 * death_monitor - Monitorea a los filósofos por muerte o finalización.
 * @arg: Puntero a la estructura de datos compartida (t_data).
 *
 * Esta función corre en un hilo separado y verifica continuamente si todos
 * los filósofos han comido (usando check_all_ate) o si algún filósofo ha
 * muerto (usando get_dead_philo). Si alguna condición se cumple, maneja la
 * situación y sale. La función duerme brevemente entre chequeos para
 * reducir el uso de CPU.
 */
void	*death_monitor(void *arg)
{
	t_data	*data;
	int		dead_idx;

	data = (t_data *)arg;
	while (1)
	{
		if (check_all_ate(data))
			return (NULL);
		dead_idx = get_dead_philo(data);
		if (dead_idx != -1)
		{
			handle_philo_death(data, dead_idx);
			return (NULL);
		}
		usleep(5000);
	}
	return (NULL);
}
