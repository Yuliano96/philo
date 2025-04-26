/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:18:50 by ypacileo          #+#    #+#             */
/*   Updated: 2025/04/26 18:32:09 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

pthread_mutex_t fork_mutex;

// Función para simular dormir una cantidad de milisegundos
void precise_sleep(int ms)
{
    usleep(ms * 1000);
}

// Función para obtener el timestamp actual en milisegundos
long current_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// Función: filósofo piensa
void think(int id)
{
    printf("[%ld ms] Filósofo %d está pensando 🧠\n", current_time_ms(), id);
    precise_sleep(500); // pensar por 0.5 segundos
}

// Función: filósofo toma tenedores (lock)
void take_forks(int id)
{
    pthread_mutex_lock(&fork_mutex);
    printf("[%ld ms] Filósofo %d ha tomado los tenedores 🍴\n", current_time_ms(), id);
}

// Función: filósofo come
void eat(int id)
{
    printf("[%ld ms] Filósofo %d está comiendo 🍝\n", current_time_ms(), id);
    precise_sleep(2000); // comer por 2 segundos
}

// Función: filósofo suelta tenedores (unlock)
void put_down_forks(int id)
{
    pthread_mutex_unlock(&fork_mutex);
    printf("[%ld ms] Filósofo %d ha soltado los tenedores 🍴\n", current_time_ms(), id);
}

// Función: filósofo duerme
void sleep_philo(int id)
{
    printf("[%ld ms] Filósofo %d está durmiendo 😴\n", current_time_ms(), id);
    precise_sleep(1000); // dormir por 1 segundo
}

// Función principal de vida del filósofo
void *philosopher_life(void *arg)
{
    int id = *(int *)arg;
    int cycles = 3; // Cada filósofo repite 3 ciclos

    while (cycles--)
    {
        think(id);
        take_forks(id);
        eat(id);
        put_down_forks(id);
        sleep_philo(id);
    }
    return NULL;
}

int main(void)
{
    pthread_t philosopher_1;
    pthread_t philosopher_2;
    int id1 = 1;
    int id2 = 2;

    pthread_mutex_init(&fork_mutex, NULL);

    pthread_create(&philosopher_1, NULL, philosopher_life, &id1);
    pthread_create(&philosopher_2, NULL, philosopher_life, &id2);

    pthread_join(philosopher_1, NULL);
    pthread_join(philosopher_2, NULL);

    pthread_mutex_destroy(&fork_mutex);
    return 0;
}
