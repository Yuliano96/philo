/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:09:37 by ypacileo          #+#    #+#             */
/*   Updated: 2025/05/10 20:50:17 by yuliano          ###   ########.fr       */
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
	pthread_t		thread;           // ID del hilo que representa al filósofo
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
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
	int				all_ate;        // bandera para saber si todos comieron lo necesario
	long long		start_time;        // Momento en que empezó el programa (en milisegundos)
	int             someone_died;       // Nueva variable para control global de muerte
	t_philo			*philo; 
	pthread_t		death_monitor;
	pthread_t		meals_monitor;
	pthread_mutex_t	*forks;            // Array de mutexes, uno por cada tenedor
	pthread_mutex_t	*write_mutex;       // Mutex para proteger los printf (que no se mezclen)
    pthread_mutex_t *someone_died_mutex; // Mutex para proteger someone_died
	pthread_mutex_t	*death_mutex; //protege last_meal_time;
}	t_data;

int	ft_atoi(const char *s);
void *philosopher_life(void *arg);
int	memory_initialization(t_data **data);
int	philo_init(t_data *data);
int	data_init(t_data **data, char **argv, int argc);
int	create_threads(t_philo *philo);
void free_data(t_data **data);
void destroy_forks(t_data *data);
long get_time(void);
void think(t_philo *philo);
void take_forks(t_philo *philo);
void eat(t_philo *philo);
void put_down_forks(t_philo *philo);
void sleep_philo(t_philo *philo);
void print_state(t_philo *philo, char *str);
void	ft_usleep(size_t time_in_ms, t_philo *philo);
void	wait_thread(t_philo *philo);
void *death_monitor(void *arg);
void *meals_monitor(void *arg);
#endif
