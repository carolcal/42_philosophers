/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:07 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/24 18:35:47 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_threads(t_philo *philos, pthread_t *monitoring)
{
	int				i;

	i = 0;
	while (i < philos->data->philos_num)
	{
		printf("philo %i\n", philos[i].id);
		if (pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]) != 0)
			handle_error(THREAD_CREATE);
		i++;
	}
	if (pthread_create(monitoring, NULL, monitor, philos))
		handle_error(THREAD_CREATE);
}

void	join_threads(t_philo *philos, pthread_t monitoring)
{
	int	i;

	i = 0;
	while (i < philos->data->philos_num)
	{
		pthread_join(philos[i].thread_id, NULL);
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

int	stop(t_philo *philos)
{
	if (philos)
		return (0);
	return (1);
}
