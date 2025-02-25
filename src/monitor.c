/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:52:17 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/25 15:15:39 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	max_meals(t_philo *philos)
{
	int	i;
	int	n_philos;
	int	max_meals;

	i = 0;
	n_philos = philos->data->philos_num;
	max_meals = philos->data->meal_num;
	while (i < n_philos)
	{
		pthread_mutex_lock(&philos[i].state);
		if (philos[i].meals < max_meals)
		{
			pthread_mutex_unlock(&philos[i].state);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].state);
		i++;
	}
	return (1);
}

int	starvation(t_philo *philos)
{
	int	i;
	int	n_philos;
	int	die_time;
	int	now;

	i = 0;
	n_philos = philos->data->philos_num;
	die_time = philos->data->die_time;
	now = get_time();
	while (i < n_philos)
	{
		pthread_mutex_lock(&philos[i].state);
		if (now - philos[i].last_meal >= die_time)
		{
			print_action(&philos[i], DIE);
			pthread_mutex_unlock(&philos[i].state);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].state);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;

	while (!stop(philos, 0))
	{
		if (philos->data->meal_num > 0 && max_meals(philos))
			stop(philos, 1);
		if (starvation(philos))
			stop(philos, 1);
	}
	return (NULL);
}
