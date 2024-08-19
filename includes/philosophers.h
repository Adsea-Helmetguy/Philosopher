/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:36:58 by mlow              #+#    #+#             */
/*   Updated: 2024/01/02 15:55:07 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

//struct
typedef struct s_philo
{
	int					id;
	int					last_meal;
	bool				is_eating;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					number_of_meals;
	bool				eaten;
	pthread_t			thread_id;
	struct s_thread		*thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}	t_philo;

//struct
typedef struct s_thread {
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					number_of_meals;
	int					num_philo_that_ate;
	int					starting_time;
	int					philosopher_dead;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		monitoring_eat_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		philo_dead_mutex;
	pthread_mutex_t		philo_that_ate_mutex;
	t_philo				*philosophers;
}				t_thread;

//philosophers.c
void	pthreading(int argc, char **argv);
void	state_philosophers(t_thread *data);
int		initialise_philosophers(t_thread *data);

//print_msg.c
void	*print_message(void *ptr);

//checker.c
int		variables_checker(t_thread *data, char **argv);
int		mutex_checker(t_thread *data);
bool	variables_structs(t_thread *data, char **argv);
bool	multiple_checker(char **argv);

//ft_atoi.c
long	ft_atol(const char *nptr);

//routine.c
void	*eatsleepthink(void *data_p);
void	begin_philosophers_routine(t_thread *data);

//rules.c
int		philo_take_forks(t_philo *philo);
void	philo_is_eating(t_philo *philo);
void	philo_is_sleeping(t_philo *philo);
void	philo_is_thinking(t_philo *philo);
int		philo_died(t_philo *philo);

//utils.c
int		get_time(void);
long	ftps_isdigit_atol(int c);
void	ft_sleep(int time);
void	ft_sleep_eating(int time, t_philo *philo);
void	print_msg(t_philo *philo, char *msg);

//utils2.c
int		checking_last_meal(t_philo *philo);
int		checking_if_philo_died(t_thread *data);
void	*monitoring_dead(void *arg);
int		monitoring_eat_finish(void *arg);

#endif
/*
#include <unistd.h> // for fork() / execve() / access()
#include <stdio.h> // for printf()
#include <stdlib.h> // exit()
#include <fcntl.h> //open()
#include <sys/wait.h> // wait() / waitpid()
#include <sys/types.h> //for wait() / fork() / pid_t() / wait() / waitpid() 
#include <errno.h> // for perror()
#include <stdbool.h> // for bool
# include <pthread.h> // for defining   include ""sys/types.h""?
# include <sys/time.h> // for using gettimeofday()
*/
