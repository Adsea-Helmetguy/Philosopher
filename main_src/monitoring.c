/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:00:18 by mlow              #+#    #+#             */
/*   Updated: 2024/02/20 19:00:35 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//change the printf
//fix normainate
int	checking_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->thread->meal_mutex);
	if ((get_time() - philo->last_meal) >= philo->thread->time_to_die
		&& philo->is_eating == false)
	{
		pthread_mutex_unlock(&philo->thread->meal_mutex);
		pthread_mutex_lock(&philo->thread->philo_dead_mutex);
		philo->thread->philosopher_dead = 1;
		pthread_mutex_unlock(&philo->thread->philo_dead_mutex);
		pthread_mutex_lock(&philo->thread->print_mutex);
		printf("[%d ms] [%d] died\n",
			(get_time() - philo->thread->starting_time), philo->id);
		pthread_mutex_unlock(&philo->thread->print_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->thread->meal_mutex);
		return (0);
	}
}

int	checking_if_philo_died(t_thread *data)
{
	int		index;

	index = -1;
	while (++index < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->monitoring_eat_mutex);
		if (!data->philosophers[index].eaten
			&& checking_last_meal(&data->philosophers[index]) != 0)
		{
			pthread_mutex_unlock(&data->monitoring_eat_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->monitoring_eat_mutex);
	}
	return (0);
}

void	*monitoring_dead(void *arg)
{
	t_thread	*data;

	data = (t_thread *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (checking_if_philo_died(data) != 0)
		{
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->dead_mutex);
		if (monitoring_eat_finish(arg) == 1)
			break ;
	}
	return (0);
}

int	monitoring_eat_finish(void *arg)
{
	t_thread	*data;

	data = (t_thread *)arg;
	pthread_mutex_lock(&data->philo_that_ate_mutex);
	if (data->num_philo_that_ate == data->number_of_philosophers)
	{
		printf("All have eaten\n");
		pthread_mutex_unlock(&data->philo_that_ate_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->philo_that_ate_mutex);
	return (0);
}
