/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:12:37 by mlow              #+#    #+#             */
/*   Updated: 2024/02/14 19:12:54 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	eatsleepthink_whileloop(t_philo *philo)
{
	while ((philo->thread->philosopher_dead) == 0)
	{
		pthread_mutex_unlock(&philo->thread->philo_dead_mutex);
		philo_take_forks(philo);
		philo_is_eating(philo);
		pthread_mutex_lock(&philo->thread->monitoring_eat_mutex);
		if (philo->number_of_meals == philo->thread->number_of_meals
			&& philo->eaten == false && philo->thread->number_of_meals != -1)
		{
			pthread_mutex_lock(&philo->thread->philo_that_ate_mutex);
			philo->thread->num_philo_that_ate++;
			pthread_mutex_unlock(&philo->thread->philo_that_ate_mutex);
			philo->eaten = true;
		}
		pthread_mutex_unlock(&philo->thread->monitoring_eat_mutex);
		philo_is_sleeping(philo);
		philo_is_thinking(philo);
		if (philo->eaten)
		{
			pthread_mutex_lock(&philo->thread->philo_dead_mutex);
			break ;
		}
		pthread_mutex_lock(&philo->thread->philo_dead_mutex);
	}
}

void	*eatsleepthink(void *data_p)
{
	t_philo	*philo;

	philo = (t_philo *)data_p;
	if (philo->id % 2 != 0)
		ft_sleep(1);
	pthread_mutex_lock(&philo->thread->philo_dead_mutex);
	eatsleepthink_whileloop(philo);
	pthread_mutex_unlock(&philo->thread->philo_dead_mutex);
	return (0);
}

/*
		printf("-----------------------------------------\n");
		printf("----\ttesting Philo.id[%d]\n",
			data->philosophers[index].id);
		printf("\ttesting Philo.time_to_eat[%d]\n",
			data->philosophers[index].time_to_eat);
		printf("\ttesting Philo.time_to_die[%d]\n",
			data->philosophers[index].time_to_die);
		printf("\ttesting Philo.last_meal[%d]\n",
			data->philosophers[index].last_meal);
		printf("----\tstarting philosophers routine\n");
		printf("-----------------------------------------\n");
*/
void	begin_philosophers_routine(t_thread *data)
{
	int	index;

	data->starting_time = get_time();
	index = -1;
	while (++index < data->number_of_philosophers)
	{
		data->philosophers[index].last_meal = get_time();
		pthread_create(&data->philosophers[index].thread_id,
			NULL, &eatsleepthink, (void *)&data->philosophers[index]);
	}
	monitoring_dead((void *)data);
	index = -1;
	while (++index < data->number_of_philosophers)
		pthread_join(data->philosophers[index].thread_id, NULL);
}
