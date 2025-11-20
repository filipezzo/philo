/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:34:39 by fsousa            #+#    #+#             */
/*   Updated: 2025/11/20 17:34:39 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	long			meals;
	long			last_meal;
	pthread_t		thread;
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	int				n_philos;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			must_eat;
	long			start_time;
	int				stop_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_mtx;
	t_philo			*philos;
}					t_data;

int					error(const char *message);
int					error2(const char *msg, const char *name);
int					is_space(char c);
int					is_digit(char c);
long				ph_atol(const char *str);
int					parse_args(int argc, char **argv, t_data *data);
int					init_data(t_data *data);
int					init_philos(t_data *data);
long				get_time_ms(void);
void				safe_print(t_data *data, int id, const char *msg);
void				*philo_routine(void *arg);
void				*monitor_routine(void *arg);
int					start_simulation(t_data *data);
void				cleanup(t_data *data);
void				smart_sleep(t_data *data, long wakeup);
#endif