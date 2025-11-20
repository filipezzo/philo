/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:13:07 by fsousa            #+#    #+#             */
/*   Updated: 2025/11/20 18:13:11 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	increase_philo_finish_meal(size_t i, t_data *data, int *finished)
{
	if (data->must_eat > 0 && data->philos[i].meals >= data->must_eat)
		(*finished)++;
}

static int	handle_monitor_death(t_data *data, int *finished)
{
	size_t	i;
	long	now;
	long	diff;

	i = 0;
	while (i < (size_t)data->n_philos)
	{
		pthread_mutex_lock(&data->lock_mtx);
		if (data->stop_simulation)
			return (pthread_mutex_unlock(&data->lock_mtx), 0);
		now = get_time_ms();
		diff = now - data->philos[i].last_meal;
		if (diff > data->t_die)
		{
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->lock_mtx);
			safe_print(data, data->philos[i].id, "died");
			return (0);
		}
		increase_philo_finish_meal(i, data, finished);
		pthread_mutex_unlock(&data->lock_mtx);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		finished;

	data = (t_data *)arg;
	while (1)
	{
		finished = 0;
		if (!handle_monitor_death(data, &finished))
			return (NULL);
		if (data->must_eat > 0 && finished == data->n_philos)
		{
			pthread_mutex_lock(&data->lock_mtx);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->lock_mtx);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
