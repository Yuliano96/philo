/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:30:21 by yuliano           #+#    #+#             */
/*   Updated: 2025/05/11 00:04:52 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->data->someone_died_mutex);
    if (philo->data->someone_died)
    {
        pthread_mutex_unlock(philo->data->someone_died_mutex);
        return;
    }
    pthread_mutex_unlock(philo->data->someone_died_mutex);
	
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

// Suelta los tenedores con sincronización adecuada
void put_down_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(philo->left_fork);
        print_state(philo, "has put down the left fork");
        pthread_mutex_unlock(philo->right_fork);
        print_state(philo, "has put down the right fork");
    }
    else
    {
        pthread_mutex_unlock(philo->right_fork);
        print_state(philo, "has put down the right fork");
        pthread_mutex_unlock(philo->left_fork);
        print_state(philo, "has put down the left fork");
    }
}

void eat(t_philo *philo)
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

void think(t_philo *philo)
{
    print_state(philo, "is thinking");
}

void sleep_philo(t_philo *philo)
{
    print_state(philo, "is sleeping");
    ft_usleep(philo->data->time_to_sleep, philo);
}

void ft_usleep(size_t time_in_ms, t_philo *philo)
{
    size_t start;

    start = get_time();
    while ((get_time() - start) < time_in_ms)
    {
        usleep(250);
        pthread_mutex_lock(philo->data->someone_died_mutex);
        if (philo->data->someone_died)
        {
            pthread_mutex_unlock(philo->data->someone_died_mutex);
            break;
        }
        pthread_mutex_unlock(philo->data->someone_died_mutex);
    }
}

void *philosopher_life(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
        ft_usleep(1, philo);
    while (1)
    {
        pthread_mutex_lock(philo->data->someone_died_mutex);
        if (philo->data->someone_died)
        {
            pthread_mutex_unlock(philo->data->someone_died_mutex);
            break;
        }
        pthread_mutex_unlock(philo->data->someone_died_mutex);

        if (philo->data->meals_required > 0)
		{
    		pthread_mutex_lock(philo->data->death_mutex);
   			 if (philo->data->all_ate)
    		{
        		pthread_mutex_unlock(philo->data->death_mutex);
        		break;
    		}
    		pthread_mutex_unlock(philo->data->death_mutex);
		}

        think(philo);
        eat(philo);
        sleep_philo(philo);
    }
    return (NULL);
}

void *death_monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;

    while (1)
    {
        i = 0;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(data->death_mutex);
            if ((get_time() - data->philo[i].last_meal_time) > data->time_to_die)
            {
                pthread_mutex_lock(data->someone_died_mutex);
                data->someone_died = 1;
                pthread_mutex_unlock(data->someone_died_mutex);

                pthread_mutex_lock(data->write_mutex);
                printf("[%lld] philosopher %d died\n", get_time() - data->start_time, data->philo[i].id);
                pthread_mutex_unlock(data->write_mutex);

                pthread_mutex_unlock(data->death_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(data->death_mutex);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}

void *meals_monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    int done;

    while (1)
    {
        pthread_mutex_lock(data->someone_died_mutex);
        if (data->someone_died)
        {
            pthread_mutex_unlock(data->someone_died_mutex);
            break;
        }
        pthread_mutex_unlock(data->someone_died_mutex);

        done = 1;
		i = 0;
		while (i < data->num_philos)
		{
    		pthread_mutex_lock(data->death_mutex);
    		if (data->philo[i].meals_eaten < data->meals_required)
        		done = 0;
    		pthread_mutex_unlock(data->death_mutex);

   	 		if (!done)
       			break;
    		i++;
		}
		if (done)
		{	
    		pthread_mutex_lock(data->death_mutex);
    		data->all_ate = 1;
    		pthread_mutex_unlock(data->death_mutex);
    		break;
		}

        usleep(1000);
    }
    return (NULL);
}








