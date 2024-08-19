/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:03:57 by mlow              #+#    #+#             */
/*   Updated: 2024/02/17 13:20:14 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//1000 cause thats's milliseconds (0.001)
// current time(get_time_day) - start time(get_time_day);
int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	ftps_isdigit_atol(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

void	ft_sleep(int time)
{
	int	start;

	start = get_time();
	while ((get_time() - start) < (time))
	{
		usleep(1000);
	}
}

void	print_msg(t_philo *philo, char *msg)
{
	if (!philo_died(philo))
	{
		pthread_mutex_lock(&philo->thread->print_mutex);
		printf("[%d ms] [%d]->%s",
			(get_time() - philo->thread->starting_time), philo->id, msg);
		pthread_mutex_unlock(&philo->thread->print_mutex);
	}
}
