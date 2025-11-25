/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsousa <fsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 17:15:35 by fsousa            #+#    #+#             */
/*   Updated: 2025/11/21 15:02:23 by fsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg_count(int argc)
{
	if (argc != 5 && argc != 6)
		return (error("./philo n_philos t_die t_eat t_sleep [must_eat]"));
	return (1);
}

static int	is_number_str(const char *str)
{
	size_t	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	if (!is_digit(str[i]))
		return (0);
	while (is_digit(str[i]))
		i++;
	while (is_space(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static long	parse_positive_arg(const char *str, const char *name)
{
	long	value;

	if (!is_number_str(str))
		return (error2("Invalid format for", name));
	value = ph_atol(str);
	if (value <= 0)
		return (error2("The value must be greater than 0 for", name));
	return (value);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (!check_arg_count(argc))
		return (0);
	data->n_philos = parse_positive_arg(argv[1], "number_of_philosophers");
	data->t_die = parse_positive_arg(argv[2], "time_to_die");
	data->t_eat = parse_positive_arg(argv[3], "time_to_eat");
	data->t_sleep = parse_positive_arg(argv[4], "time_to_sleep");
	if (!data->n_philos || !data->t_die || !data->t_eat || !data->t_sleep)
		return (0);
	if (argc == 6)
	{
		data->must_eat = parse_positive_arg(argv[5], "must eat");
		if (!data->must_eat)
			return (0);
	}
	else
		data->must_eat = -1;
	return (1);
}
