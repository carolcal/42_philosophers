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

void	take_forks(t_philo *philo)
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
}
void	p_eat(t_philo *philo, int eat_time)
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
}

void	p_sleep(t_philo *philo, int sleep_time)
{
	print_action(philo, SLEEP);
	usleep(sleep_time * 1000);
}

void	p_think(t_philo *philo)
{
	print_action(philo, THINK);
	while (1)
		usleep(1);
}

void	*routine(void *arg)
{
	t_philo *philos;
	int	i;

	philos = (t_philo *)arg;
	i = 0;
	while (!stop(philos))
	{
		p_eat(&philos[i], philos[i].data->eat_time);
		p_sleep(&philos[i], philos[i].data->sleep_time);
		p_think(&philos[i]);
		i++;
	}
	return (NULL);
}
