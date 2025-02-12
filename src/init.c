/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:33:19 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/12 17:42:47 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*init_forks(int num)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = malloc(num * sizeof(t_fork));
	if (!forks)
		handle_error(MALLOC_FAILED);
	while (i < num)
	{
		forks[i].id = i;
		pthread_mutex_init(&forks[i].state, NULL);
		i++;
	}
	return (forks);
}

t_fork	*assign_fork(t_data *data, t_philo philo, char side)
{
	int		fork_id;
	int		i;

	i = 0;
	if (side == 'l')
		fork_id = philo.id;
	else
	{
		if (philo.id == 0)
			fork_id = data->philos_num - 1;
		else
			fork_id = philo.id - 1;
	}
	while (i < data->philos_num)
	{
		if (data->forks[i].id == fork_id)
			return (&data->forks[i]);
		i++;
	}
	return (NULL);
}

t_philo	*init_philos(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(data->philos_num * sizeof(t_philo));
	if (!philos)
		handle_error(MALLOC_FAILED);
	while (i < data->philos_num)
	{
		philos[i].id = i;
		philos[i].meals = 0;
		philos[i].r_fork = assign_fork(data, philos[i], 'r');
		philos[i].l_fork = assign_fork(data, philos[i], 'l');
		i++;
	}
	return (philos);
}

t_data	*init_data(char *av[])
{
	t_data			*data;

	data = malloc(sizeof(data));
	if (!data)
		handle_error(MALLOC_FAILED);
	data->philos_num = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (av[5])
		data->meal_num = ft_atoi(av[5]);
	else
		data->meal_num = -1;
	data->start_time = 0;
	verify_args(data, av[5]);
	data->forks = init_forks(data->philos_num);
	data->philos = init_philos(data);
	return (data);
}
