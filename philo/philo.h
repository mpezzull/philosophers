/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-rosa <mde-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:27:36 by mde-rosa          #+#    #+#             */
/*   Updated: 2021/10/05 19:40:12 by mde-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

# define ERROR		-1
# define OFLOW		-2
# define GOOD		3
# define ARGVALUE	4
# define EOL		'\0'

typedef struct s_philo
{
	pthread_mutex_t	eating;
	pthread_t		thd_philo;
	pthread_t		killer;
	int				pid;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	int				is_eating;
	long long		last_time_ate;
	struct s_din	*table;
}				t_philo;

typedef struct s_din
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	t_philo			**philos;
	long long		start_time;
	int				death;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
}	t_din;

t_philo				**initialize_philosphers(t_din *table);
pthread_mutex_t		*initialize_forks(t_din *table);
int					ft_is_number(char *string);
int					ft_check(unsigned long pt, int s);
long long			ft_time_in_ms(void);
int					ft_atoi_check(const char *str);
void				*start_routine(void *data);
void				print_status(t_din *table, int pid, char *string);

#endif
