/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:07 by cayamash          #+#    #+#             */
/*   Updated: 2025/03/06 15:41:03 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	start_threads(t_philo *philos, pthread_t *monitoring)
{
	int				i;

	i = 0;
	while (i < philos->data->philos_num)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			handle_error(THREAD_CREATE);
		i++;
	}
	if (pthread_create(monitoring, NULL, monitor, philos))
		handle_error(THREAD_CREATE);
}

static void	join_threads(t_philo *philos, pthread_t monitoring)
{
	int	i;

	i = 0;
	while (i < philos->data->philos_num)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitoring, NULL);
}

void	start(t_philo *philos)
{
	pthread_t	monitoring;

	start_threads(philos, &monitoring);
	join_threads(philos, monitoring);
}

int	stop(t_philo *philos, int stop)
{
	int	flag;

	pthread_mutex_lock(&philos->data->state);
	if (stop)
		philos->data->flag = 1;
	flag = philos->data->flag;
	pthread_mutex_unlock(&philos->data->state);
	return (flag);
}
