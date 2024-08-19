/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:47:16 by mlow              #+#    #+#             */
/*   Updated: 2024/02/18 14:48:07 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	philo_take_forks(t_philo *philo)
{
	philo_died(philo);
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken a fork\n");
	if (philo->thread->number_of_philosophers == 1)
	{
		ft_sleep(philo->thread->time_to_die);
		pthread_mutex_lock(&philo->thread->philo_dead_mutex);
		philo->thread->philosopher_dead = 1;
		pthread_mutex_unlock(&philo->thread->philo_dead_mutex);
		return (1);
	}
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken the other fork\n");
	return (0);
}

//
//The one below does not work for me
/*
int	philo_take_forks(t_philo *philo)
{
	philo_died(philo);
	if (philo->id % 2 != 0)
		pthread_mutex_lock(philo->right_fork);
	else if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_fork);
	print_msg(philo, "has taken a fork\n");
	if (philo->thread->number_of_philosophers == 1)
	{
		ft_sleep(philo->thread->time_to_die);
		pthread_mutex_lock(&philo->thread->philo_dead_mutex);
		philo->thread->philosopher_dead = 1;
		pthread_mutex_unlock(&philo->thread->philo_dead_mutex);
		return (1);
	}
	if (philo->id % 2 != 0)
		pthread_mutex_lock(philo->left_fork);
	else if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	print_msg(philo, "has taken the other fork\n");
	return (0);
}
*/
/*
int	philo_take_forks(t_philo *philo)
{
	pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    philo_died(philo);
    if (philo->right_fork < philo->left_fork) 
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    } 
    else 
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
	pthread_mutex_lock(first_fork);
	print_msg(philo, "has taken a fork\n");
	if (philo->thread->number_of_philosophers == 1)
	{
		ft_sleep(philo->thread->time_to_die);
		pthread_mutex_lock(&philo->thread->philo_dead_mutex);
		philo->thread->philosopher_dead = 1;
		pthread_mutex_unlock(&philo->thread->philo_dead_mutex);
		return (1);
	}
	pthread_mutex_lock(second_fork);
	print_msg(philo, "has taken the other fork\n");
	return (0);
}
*/
//
/*
-add this in if u want to see how they eat meals-
-this is not protected by mutex lock so don't use 
this to test- remove this part later:
================================================================
		printf("\nphilo[%d]->number of meals: %d\n\n",
			philo->id, philo->number_of_meals);
================================================================
	if (!philo_died(philo))
	{
		if (philo->number_of_meals != -1)
			philo->number_of_meals++;
		printf("\nphilo[%d]->number of meals: %d\n\n",
			philo->id, philo->number_of_meals);
	}
*/
void	philo_is_eating(t_philo *philo)
{
	philo_died(philo);
	print_msg(philo, "is eating\n");
	philo->is_eating = true;
	pthread_mutex_lock(&philo->thread->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->thread->meal_mutex);
	ft_sleep(philo->thread->time_to_eat);
	pthread_mutex_lock(&philo->thread->meal_mutex);
	if (!philo_died(philo))
	{
		if (philo->number_of_meals != -1)
			philo->number_of_meals++;
	}
	pthread_mutex_unlock(&philo->thread->meal_mutex);
	philo->is_eating = false;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_is_sleeping(t_philo *philo)
{
	if (!philo_died(philo))
	{
		if (!philo->eaten)
			print_msg(philo, "is sleeping\n");
		ft_sleep(philo->thread->time_to_sleep);
	}
}

void	philo_is_thinking(t_philo *philo)
{	
	if (!philo_died(philo))
	{
		if (!philo->eaten)
			print_msg(philo, "is thinking\n");
		usleep(100);
	}
}

int	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->thread->philo_dead_mutex);
	if (philo->thread->philosopher_dead == 1)
	{
		pthread_mutex_unlock(&philo->thread->philo_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->thread->philo_dead_mutex);
	return (0);
}
