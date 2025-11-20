/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:15:51 by fsousa            #+#    #+#             */
/*   Updated: 2025/11/20 17:42:42 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(const char *msg)
{
	printf("Error: %s\n", msg);
	return (0);
}

int	error2(const char *msg, const char *name)
{
	printf("Error: %s %s\n", msg, name);
	return (0);
}
