/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_thread_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:59:14 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/22 22:02:59 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Inicializa la memoria necesaria para los mutex y estructuras de filósofos
int	memory_initialization(t_data **data)
{
	(*data)->forks = malloc(sizeof(pthread_mutex_t) * (*data)->num_philos);
	if (!(*data)->forks)
		return (0);
	(*data)->philo = malloc(sizeof(t_philo) * (*data)->num_philos);
	if (!(*data)->philo)
		return (0);
	(*data)->write_mutex = malloc(sizeof(pthread_mutex_t));
	if (!(*data)->write_mutex)
		return (0);
	(*data)->death_mutex = malloc(sizeof(pthread_mutex_t));
	if (!(*data)->death_mutex)
		return (0);
	(*data)->someone_died_mutex = malloc(sizeof(pthread_mutex_t));
	if (!(*data)->someone_died_mutex)
		return (0);
	return (1);
}

// Espera a que todos los hilos de los filósofos terminen
void	wait_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

// Inicializa los mutex de los tenedores
int	mutex_init_forks(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->num_philos)
	{
		if (pthread_mutex_init(&(*data)->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

// Crea los hilos para cada filósofo
int	create_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, \
			philosopher_life, &philo[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
