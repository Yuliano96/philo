/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypacileo <ypacileo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:09:37 by ypacileo          #+#    #+#             */
/*   Updated: 2025/04/26 19:54:56 by ypacileo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Librerías necesarias
# include <pthread.h>    // Para usar hilos (pthread_create) y mutexes (pthread_mutex)
# include <sys/time.h>   // Para medir el tiempo con gettimeofday
# include <stdlib.h>     // Para malloc, free, exit, etc
# include <unistd.h>     // Para usleep, write
# include <stdio.h>      // Para printf (debug o mensajes)

/////////////////////////
// Declaraciones previas
/////////////////////////

// Forward declaration para evitar problemas de dependencia circular
struct s_data;

/////////////////////////
// Estructura del Filósofo
/////////////////////////

typedef struct s_philo
{
	pthread_t		thread;            // ID del hilo que representa al filósofo
	int				id;                // Número identificador del filósofo (1, 2, 3, etc)
	int				meals_eaten;       // Número de veces que ha comido
	long long		last_meal_time;    // Tiempo en el que hizo su última comida (en milisegundos)
	struct s_data	*data;             // Puntero a la estructura principal (datos globales)
}	t_philo;

/////////////////////////
// Estructura de Datos Globales
/////////////////////////

typedef struct s_data
{
	int				num_philos;        // Número total de filósofos
	int				time_to_die;       // Tiempo máximo que puede pasar sin comer antes de morir (ms)
	int				time_to_eat;       // Tiempo que tarda en comer (ms)
	int				time_to_sleep;     // Tiempo que tarda en dormir (ms)
	int				meals_required;    // Número de comidas requeridas (opcional, según bonus)
	long long		start_time;        // Momento en que empezó el programa (en milisegundos)

	pthread_mutex_t	*forks;            // Array de mutexes, uno por cada tenedor
	t_philo			*philos;           // Array de filósofos

	pthread_mutex_t	write_mutex;       // Mutex para proteger los printf (que no se mezclen)
	pthread_mutex_t	death_mutex;       // Mutex para proteger el estado de muerte (variable dead)
	
	int				dead;              // 0 = vivo, 1 = alguien murió (controla la finalización)
}	t_data;

#endif
