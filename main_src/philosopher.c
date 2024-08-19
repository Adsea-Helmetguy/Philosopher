/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:10:58 by mlow              #+#    #+#             */
/*   Updated: 2024/02/13 16:11:16 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	initialise_philosophers(t_thread *data)
{
	int	index;

	index = -1;
	data->philosophers = (t_philo *)malloc(sizeof(t_philo)
			* data->number_of_philosophers);
	if (!data->philosophers)
		return (1);
	while (++index < data->number_of_philosophers)
	{
		data->philosophers[index].id = index + 1;
		data->philosophers[index].last_meal = 0;
		data->philosophers[index].is_eating = false;
		data->philosophers[index].time_to_die = data->time_to_die;
		data->philosophers[index].time_to_eat = data->time_to_eat;
		data->philosophers[index].time_to_sleep = data->time_to_sleep;
		data->philosophers[index].number_of_meals = 0;
		data->philosophers[index].eaten = false;
		data->philosophers[index].left_fork = &data->fork_mutex[index];
		data->philosophers[index].right_fork
			= &data->fork_mutex[((index + 1)
				% data->number_of_philosophers)];
		data->philosophers[index].thread = data;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_thread	data;

	if (argc < 5 || argc > 6)
		printf("Invalid arguments");
	else if (argc == 5 || argc == 6)
	{
		if (variables_checker(&data, argv))
		{
			begin_philosophers_routine(&data);
			free(data.philosophers);
			free(data.fork_mutex);
		}
	}
	return (0);
}
