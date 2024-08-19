/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:20:50 by mlow              #+#    #+#             */
/*   Updated: 2024/02/14 15:21:10 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	variables_checker(t_thread *data, char **argv)
{
	bool	true_false;

	data->number_of_philosophers = 0;
	data->time_to_die = 0;
	data->time_to_sleep = 0;
	data->time_to_eat = 0;
	data->number_of_meals = 0;
	data->num_philo_that_ate = 0;
	data->starting_time = 0;
	data->philosopher_dead = 0;
	multiple_checker(argv);
	true_false = variables_structs(data, argv);
	return (true_false);
}

int	mutex_checker(t_thread *data)
{
	int	index;

	index = 0;
	data->fork_mutex
		= (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!(data)->fork_mutex)
		return (1);
	while (index < data->number_of_philosophers)
	{
		pthread_mutex_init(&(data)->fork_mutex[index], NULL);
		index++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->monitoring_eat_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->philo_dead_mutex, NULL);
	pthread_mutex_init(&data->philo_that_ate_mutex, NULL);
	return (0);
}

bool	variables_structs(t_thread *data, char **argv)
{	
	data->number_of_philosophers = ft_atol(argv[1]);
	if (data->number_of_philosophers <= 0)
		return (false);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		data->number_of_meals = ft_atol(argv[5]);
	else
		data->number_of_meals = -1;
	if (mutex_checker(data) == 1)
		return (false);
	if (initialise_philosophers(data) == 1)
		return (false);
	return (true);
}

bool	multiple_checker(char **argv)
{
	int	array;
	int	index;

	array = 0;
	while (argv[++array])
	{
		index = -1;
		while (argv[array][++index])
		{
			if (index == 0 && argv[array][index] == '-')
				return (false);
			if (!ftps_isdigit_atol(argv[array][index]))
				return (false);
		}
	}
	return (true);
}
