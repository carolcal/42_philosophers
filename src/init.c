/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:33:19 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/06 15:54:02 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_fork	*init_forks(int num)
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

static t_fork	*assign_fork(t_data *data, t_philo philo, char side)
{
	int	fork_id;

	if (side == 'r')
		fork_id = philo.id;
	else
		fork_id = (philo.id + 1) % data->philos_num;
	return (&data->forks[fork_id]);
}

static t_philo	*init_philos(t_data *data)
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
		philos[i].last_meal = 0;
		philos[i].meals = 0;
		philos[i].r_fork = assign_fork(data, philos[i], 'r');
		philos[i].l_fork = assign_fork(data, philos[i], 'l');
		pthread_mutex_init(&philos[i].state, NULL);
		philos[i].data = data;
		i++;
	}
	return (philos);
}

static t_data	*init_data(char *av[])
{
	t_data			*data;

	data = malloc(sizeof(t_data));
	if (!data)
		handle_error(MALLOC_FAILED);
	data->philos_num = ft_atoi(av[1]);
	data->die_time = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	data->init_time = 0;
	if (av[5])
	data->meal_num = ft_atoi(av[5]);
	else
	data->meal_num = -1;
	verify_args(data, av[5]);
	data->flag = 0;
	pthread_mutex_init(&data->state, NULL);
	data->init_time = get_time(data);
	data->forks = init_forks(data->philos_num);
	return (data);
}

t_philo	*init(char *av[])
{
	t_data	*data;
	t_philo	*philos;

	data = init_data(av);
	philos = init_philos(data);
	return (philos);
}
