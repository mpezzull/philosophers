/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-rosa <mde-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:26:23 by mde-rosa          #+#    #+#             */
/*   Updated: 2021/10/05 19:41:53 by mde-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_din *table, int pid, char *string)
{
	pthread_mutex_lock(&table->write);
	printf("%lld %d %s", ft_time_in_ms() - table->start_time, pid + 1, string);
	if (string[0] != 'd')
		pthread_mutex_unlock(&table->write);
}

void	eat_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	print_status(philo->table, philo->pid, "taken left fork\n");
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	print_status(philo->table, philo->pid, "taken right fork\n");
	pthread_mutex_lock(&philo->eating);
	print_status(philo->table, philo->pid, "is eating\n");
	philo->last_time_ate = ft_time_in_ms();
	philo->is_eating = 1;
	usleep(philo->table->time_to_eat * 1000 - 20000);
	while (ft_time_in_ms() - philo->last_time_ate < philo->table->time_to_eat)
		continue ;
	philo->meals_eaten++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eating);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	return ;
}

void	sleep_routine(t_philo *philo)
{
	long long	time;

	print_status(philo->table, philo->pid, "is sleeping\n");
	time = ft_time_in_ms();
	usleep(philo->table->time_to_sleep * 1000 - 20000);
	while (ft_time_in_ms() - time < philo->table->time_to_sleep)
		continue ;
	return ;
}

void	think_routine(t_philo *philo)
{
	print_status(philo->table, philo->pid, "is thinking\n");
	return ;
}

void	*start_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->table->death)
	{
		eat_routine(philo);
		sleep_routine(philo);
		think_routine(philo);
		usleep(100);
	}
	return (NULL);
}
