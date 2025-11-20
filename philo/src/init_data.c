/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:15:22 by fsousa            #+#    #+#             */
/*   Updated: 2025/11/20 18:22:51 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialize_data(t_data *data)
{
	data->start_time = 0;
	data->stop_simulation = 0;
	data->philos = NULL;
	data->forks = NULL;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (error("Malloc failed for forks"));
	return (1);
}

static int	initialize_global_mutex(t_data *data)
{
	size_t	i;

	if (pthread_mutex_init(&data->lock_mtx, NULL) != 0)
	{
		i = 0;
		while (i < (size_t)data->n_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
		data->forks = NULL;
		return (error("failed to init global mutex"));
	}
	return (1);
}

int	init_data(t_data *data)
{
	size_t	i;
	size_t	j;

	if (!initialize_data(data))
		return (0);
	i = 0;
	while (i < (size_t)data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&data->forks[j]);
				j++;
			}
			free(data->forks);
			data->forks = NULL;
			return (error("fail to init fork mutex"));
		}
		i++;
	}
	if (!initialize_global_mutex(data))
		return (0);
	return (1);
}
