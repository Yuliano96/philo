/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:18:50 by ypacileo          #+#    #+#             */
/*   Updated: 2025/05/11 00:04:57 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(const char *s)
{
    int i = 0;
    long number = 0;
    int sign = 1;

    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r'
        || s[i] == '\v' || s[i] == '\f')
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
        number = number * 10 + s[i] - '0';
        i++;
    }
    return (number * sign);
}

int validate_args(int argc, char **argv)
{
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_required;

    if (argc == 6)
    {
        num_philos = ft_atoi(argv[1]);
        time_to_die = ft_atoi(argv[2]);
        time_to_eat = ft_atoi(argv[3]);
        time_to_sleep = ft_atoi(argv[4]);
        meals_required = ft_atoi(argv[5]);
        if (num_philos <= 0 || time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0 || meals_required <= 0)
            return (0);
        return (1);
    }
    else if (argc == 5)
    {
        num_philos = ft_atoi(argv[1]);
        time_to_die = ft_atoi(argv[2]);
        time_to_eat = ft_atoi(argv[3]);
        time_to_sleep = ft_atoi(argv[4]);
        if (num_philos <= 0 || time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0)
            return (0);
        return (1);
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_data *data;

    if (!validate_args(argc, argv))
    {
        printf("Error: argumentos inválidos.\n");
        return (1);
    }
    if (!data_init(&data, argv, argc))
    {
        printf("Error: fallo en la inicialización de datos.\n");
        return (1);
    }

    pthread_detach(data->death_monitor);
    if (data->meals_required > 0)
        pthread_detach(data->meals_monitor);
    wait_thread(data->philo);
    free_data(&data);
    return (0);
}