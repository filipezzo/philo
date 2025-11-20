/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:15:53 by fsousa            #+#    #+#             */
/*   Updated: 2025/11/20 17:42:11 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	time;
	long			ms;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	ms = time.tv_sec * 1000L + time.tv_usec / 1000L;
	return (ms);
}

void	smart_sleep(t_data *data, long wakeup)
{
	long	start;

	start = get_time_ms() + wakeup;
	while (get_time_ms() < start)
	{
		if (data->stop_simulation)
			break ;
		usleep(100);
	}
}
