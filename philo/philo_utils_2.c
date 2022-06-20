/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-rosa <mde-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:34:38 by mde-rosa          #+#    #+#             */
/*   Updated: 2021/10/05 19:42:17 by mde-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time_in_ms(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

t_philo	**initialize_philosphers(t_din *table)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo *) * table->num_philo + 1);
	if (philos == NULL)
		return (NULL);
	while (i < table->num_philo)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo) * 1);
		if (philos[i] == NULL)
			return (NULL);
		if (pthread_mutex_init(&philos[i]->eating, 0) != 0)
			return (NULL);
		philos[i]->table = table;
		philos[i]->pid = i;
		philos[i]->is_eating = 0;
		philos[i]->meals_eaten = 0;
		philos[i]->left_fork = i;
		philos[i]->right_fork = (i + 1) % philos[i]->table->num_philo;
		i++;
	}
	return (philos);
}

pthread_mutex_t	*initialize_forks(t_din *table)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	if (table->num_philo == OFLOW || table->time_to_die == OFLOW
		|| table->time_to_eat == OFLOW || table->time_to_sleep == OFLOW
		|| table->num_meals == OFLOW)
	{
		write(2, "Error: Invalid Argument\n", 23);
		return (NULL);
	}
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->num_philo);
	if (forks == NULL)
		return (NULL);
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}
