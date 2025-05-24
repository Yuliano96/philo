/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:30:21 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/24 14:57:12 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * take_forks - Permite que el filósofo tome los tenedores de forma segura.
 * @philo: Puntero a la estructura del filósofo.
 *
 * El orden depende del id para evitar interbloqueos.
 */
void	take_forks(t_philo *philo)
{
	if (some_died(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken the right fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken the left fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken the left fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken the right fork");
	}
}

/**
 * put_down_forks - Suelta los tenedores de forma segura.
 * @philo: Puntero a la estructura del filósofo.
 *
 * El orden depende del id para evitar interbloqueos.
 */
void	put_down_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	print_state(philo, "has put down both forks");
}

/**
 * eat - Permite que el filósofo coma y actualiza su estado.
 * @philo: Puntero a la estructura del filósofo.
 *
 * Toma los tenedores, actualiza el tiempo de la última comida y el contador,
 * imprime el estado y duerme el tiempo de comer.
 */
void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(philo->data->death_mutex);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->data->death_mutex);
	print_state(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo);
	put_down_forks(philo);
}

/**
 * sleep_philo - Hace que el filósofo duerma el tiempo indicado.
 * @philo: Puntero a la estructura del filósofo.
 */
void	sleep_philo(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
}

/**
 * philosopher_life - Función principal del hilo de cada filósofo.
 * @arg: Puntero a la estructura del filósofo.
 *
 * Ejecuta el ciclo de pensar, comer y dormir hasta que alguien muera
 * o todos hayan comido lo requerido.
 */
void	*philosopher_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(5, philo);
	while (1)
	{
		if (some_died(philo))
			break ;
		if (philo->data->meals_required > 0)
		{
			pthread_mutex_lock(philo->data->death_mutex);
			if (philo->data->all_ate)
			{
				pthread_mutex_unlock(philo->data->death_mutex);
				break ;
			}
			pthread_mutex_unlock(philo->data->death_mutex);
		}
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}
	return (NULL);
}
