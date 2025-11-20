/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:15:43 by fsousa            #+#    #+#             */
/*   Updated: 2025/11/20 18:18:28 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	waiting_threads(t_data *data, pthread_t monitor_thread)
{
	size_t	i;

	i = 0;
	while (i < (size_t)data->n_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (error("waiting for philo thread"));
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (error("waiting for monitor thread"));
	return (1);
}

int	start_simulation(t_data *data)
{
	size_t		i;
	pthread_t	monitor_thread;

	data->start_time = get_time_ms();
	pthread_mutex_lock(&data->lock_mtx);
	i = 0;
	while (i < (size_t)data->n_philos)
	{
		data->philos[i].last_meal = data->start_time;
		i++;
	}
	pthread_mutex_unlock(&data->lock_mtx);
	i = 0;
	while (i < (size_t)data->n_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (error("while creating philo thread"));
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
		return (error("while creating monitor thread"));
	if (!waiting_threads(data, monitor_thread))
		return (0);
	return (1);
}
