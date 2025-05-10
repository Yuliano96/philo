/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:39:21 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/11 00:00:56 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_state(t_philo *philo, char *str)
{
    pthread_mutex_lock(philo->data->someone_died_mutex);
    if (!philo->data->someone_died)
    {
        pthread_mutex_lock(philo->data->write_mutex);
        printf("[ %lld ms] Philosopher %d %s\n", get_time() - philo->data->start_time, philo->id, str);
        pthread_mutex_unlock(philo->data->write_mutex);
    }
    pthread_mutex_unlock(philo->data->someone_died_mutex);
}

void destroy_forks(t_data *data)
{
    int i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
}

void free_data(t_data **data)
{
    if (*data)
    {
        if ((*data)->forks)
        {
            destroy_forks(*data);
            free((*data)->forks);
        }
        if ((*data)->write_mutex)
        {
            pthread_mutex_destroy((*data)->write_mutex);
            free((*data)->write_mutex);
        }
        if ((*data)->death_mutex)
        {
            pthread_mutex_destroy((*data)->death_mutex);
            free((*data)->death_mutex);
        }
        if ((*data)->someone_died_mutex)
        {
            pthread_mutex_destroy((*data)->someone_died_mutex); 
            free((*data)->someone_died_mutex);
        }
        if ((*data)->philo)
            free((*data)->philo);
        free(*data);
        *data = NULL;
    }
}