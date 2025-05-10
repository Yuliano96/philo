/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:31:08 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/11 00:03:14 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int memory_initialization(t_data **data)
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

void wait_thread(t_philo *philo)
{
    int i = 0;
    while (i < philo->data->num_philos)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
}

int data_init(t_data **data, char **argv, int argc)
{
    int i;

    *data = malloc(sizeof(t_data));
    if (!(*data))
        return (0);

    (*data)->num_philos = ft_atoi(argv[1]);
    (*data)->time_to_die = ft_atoi(argv[2]);
    (*data)->time_to_eat = ft_atoi(argv[3]);
    (*data)->time_to_sleep = ft_atoi(argv[4]);
    (*data)->someone_died = 0;
    (*data)->all_ate = 0;
    (*data)->meals_required = (argc == 6) ? ft_atoi(argv[5]) : 0;

    if (!memory_initialization(data)) 
    {
        free_data(data);
        return (0);
    }

    i = 0;
    while (i < (*data)->num_philos)
    {
        if (pthread_mutex_init(&(*data)->forks[i], NULL) != 0)
        {
            free_data(data); 
            return (0);
        }
        i++;
    }

    if (pthread_mutex_init((*data)->write_mutex, NULL) != 0 ||
        pthread_mutex_init((*data)->death_mutex, NULL) != 0 ||
        pthread_mutex_init((*data)->someone_died_mutex, NULL) != 0)
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




// Crea los hilos para cada filósofo
int create_threads(t_philo *philo)
{
    int i;

    i = 0;
    while (i < philo->data->num_philos)
    {
        if (pthread_create(&philo[i].thread, NULL, philosopher_life, &philo[i]) != 0)
        {
            printf("Error: fallo al crear el hilo del filósofo %d\n", philo[i].id);
            return (0);
        }
        i++;
    }
    return (1);
}

// Inicializa los filósofos y sus tenedores
int philo_init(t_data *data)
{
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        data->philo[i].id = i + 1;
        data->philo[i].right_fork = &data->forks[i];
        data->philo[i].left_fork = &data->forks[(i + 1) % data->num_philos];
        data->philo[i].data = data;
		pthread_mutex_lock(data->death_mutex);
        data->philo[i].meals_eaten = 0;
        data->philo[i].last_meal_time = get_time();
        pthread_mutex_unlock(data->death_mutex);
        i++;
    }
    data->start_time = get_time();
    if (!create_threads(data->philo))
        return (0);
    if (pthread_create(&data->death_monitor, NULL, death_monitor, data) != 0)
        return (0);
    if (data->meals_required > 0) // Solo crear meals_monitor si se especificó meals_required
        if (pthread_create(&data->meals_monitor, NULL, meals_monitor, data) != 0)
            return (0);
    return (1);
}