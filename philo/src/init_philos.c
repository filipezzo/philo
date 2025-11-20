/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:15:26 by fsousa            #+#    #+#             */
/*   Updated: 2025/11/20 17:27:24 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *data)
{
	size_t	i;
	t_philo	*philo;

	data->philos = malloc(data->n_philos * sizeof(t_philo));
	if (!data->philos)
		return (error("Malloc failed for philos"));
	i = 0;
	while (i < (size_t)data->n_philos)
	{
		philo = &data->philos[i];
		philo->id = i + 1;
		philo->last_meal = 0;
		philo->meals = 0;
		philo->data = data;
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % data->n_philos];
		i++;
	}
	return (1);
}
