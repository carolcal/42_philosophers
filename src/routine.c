/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:09:06 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/24 12:09:06 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->l_fork->state);
		print_action(philo, FORK);
		pthread_mutex_lock(&philo->r_fork->state);
		print_action(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->state);
		print_action(philo, FORK);
		pthread_mutex_lock(&philo->l_fork->state);
		print_action(philo, FORK);
	}
	return (NULL);
}

static void	*eating(t_philo *philo, int eat_time)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->state);
	philo->last_meal = get_time();
	print_action(philo, EAT);
	philo->meals++;
	pthread_mutex_unlock(&philo->state);
	usleep(eat_time * 1000);
	pthread_mutex_unlock(&philo->l_fork->state);
	pthread_mutex_unlock(&philo->r_fork->state);
	return (NULL);
}

static void	*sleeping(t_philo *philo, int sleep_time)
{
	if (!stop(philo, 0))
	{
		print_action(philo, SLEEP);
		usleep(sleep_time * 1000);
	}
	return (NULL);
}

static void	*thinking(t_philo *philo)
{
	if (!stop(philo, 0))
	{
		print_action(philo, THINK);
		usleep(500);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (!stop(philos, 0))
	{
		i = 0;
		eating(&philos[i], philos[i].data->eat_time);
		sleeping(&philos[i], philos[i].data->sleep_time);
		thinking(&philos[i]);
		i++;
	}
	return (NULL);
}
