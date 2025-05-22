/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliano <yuliano@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:09:37 by ypacileo          #+#    #+#             */
/*   Updated: 2025/05/22 22:38:54 by yuliano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h> 
# include <stdio.h> 

struct	s_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_required;
	int				all_ate;
	long long		start_time;
	int				someone_died;
	t_philo			*philo;
	pthread_t		death_monitor;
	pthread_t		meals_monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*someone_died_mutex;
	pthread_mutex_t	*death_mutex;
}	t_data;

int		allocate_data(t_data **data);
int		init_arguments(t_data *data, char **argv, int argc);
int		initialize_resources(t_data **data);
int		is_positive_number(const char *str);
int		ft_atoi(const char *s);
void	*philosopher_life(void *arg);
int		memory_initialization(t_data **data);
int		mutex_init_forks(t_data **data);
int		philo_init(t_data *data);
int		data_init(t_data **data, char **argv, int argc);
int		create_threads(t_philo *philo);
void	free_data(t_data **data);
void	destroy_forks(t_data *data);
void	destroy_mutex(pthread_mutex_t **mutex);
int		some_died(t_philo *philo);
long	get_time(void);
void	think(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	put_down_forks(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	print_state(t_philo *philo, char *str);
void	ft_usleep(size_t time_in_ms, t_philo *philo);
void	wait_thread(t_philo *philo);
int		all_philos_ate(t_data *data);
int		get_dead_philo(t_data *data);
int		check_all_ate(t_data *data);
void	handle_philo_death(t_data *data, int dead_idx);
void	*death_monitor(void *arg);
void	*meals_monitor(void *arg);
#endif
