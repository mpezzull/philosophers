/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-rosa <mde-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 18:27:23 by mde-rosa          #+#    #+#             */
/*   Updated: 2021/10/05 20:08:21 by mde-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg_validity(int argSize, char **args)
{
	int	i;

	i = 1;
	if (argSize - 1 < ARGVALUE || argSize - 1 > 5)
		return (ERROR);
	while (i < argSize)
	{
		if (ft_is_number(args[i]) != GOOD)
			return (ERROR);
		i++;
	}
	return (GOOD);
}

t_din	*fill_table(int argSize, char **args)
{
	t_din	*table;

	table = (t_din *) malloc(sizeof(t_din) * 1);
	if (table == NULL)
		return (NULL);
	table->num_philo = ft_atoi_check(args[1]);
	table->time_to_die = ft_atoi_check(args[2]);
	table->time_to_eat = ft_atoi_check(args[3]);
	table->time_to_sleep = ft_atoi_check(args[4]);
	table->num_meals = -1;
	table->death = 1;
	if (argSize - 1 == 5)
		table->num_meals = ft_atoi_check(args[5]);
	table->forks = initialize_forks(table);
	if (table->forks == NULL)
		return (NULL);
	table->philos = initialize_philosphers(table);
	if (table->philos == NULL || table->num_philo == 0)
		return (NULL);
	if (pthread_mutex_init(&table->write, 0) != 0)
		return (NULL);
	return (table);
}

void	*black_mamba(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (philo->table->death)
	{
		if (!philo->is_eating && ft_time_in_ms() - philo->last_time_ate
			>= philo->table->time_to_die)
		{
			pthread_mutex_lock(&philo->eating);
			print_status(philo->table, philo->pid, "died\n");
			philo->table->death = 0;
			pthread_mutex_unlock(&philo->eating);
		}
		if (philo->table->philos[philo->table->num_philo - 1]->meals_eaten
			== philo->table->num_meals)
			philo->table->death = 0;
		usleep(100);
	}
	return (NULL);
}

int	start_threads(t_din *table)
{
	int	i;

	i = 0;
	table->start_time = ft_time_in_ms();
	while (i < table->num_philo)
	{
		table->philos[i]->last_time_ate = ft_time_in_ms();
		if (pthread_create(&table->philos[i]->thd_philo, NULL,
				&start_routine, (void *)table->philos[i]) != 0)
			return (ERROR);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philos[i]->killer, NULL, &black_mamba,
				(void *)table->philos[i]) != 0)
			return (ERROR);
		usleep(100);
		i++;
	}
	while (table->death)
		continue ;
	return (GOOD);
}

int	main(int argc, char **argv)
{
	t_din	*table;
	int		p_counter;

	p_counter = 0;
	table = NULL;
	if (check_arg_validity(argc, argv) != GOOD)
	{
		write(2, "Error: Invalid Argument\n", 23);
		return (ERROR);
	}
	table = fill_table(argc, argv);
	if (table == NULL)
		return (ERROR);
	if (start_threads(table) != GOOD)
		return (ERROR);
	return (GOOD);
}
