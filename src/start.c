/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:07 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/19 17:30:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	int i = 0;
	const char *arr[] = {FORK, EAT, SLEEP, THINK, DIE};

	while (i < 4)
	{
		printf("Philosopher %d %s\n", philo->id, arr[i]);
		i++;
	}
	return (NULL);
}

void	start_threads(t_data *data, pthread_t *monitoring)
{
	int				i;
	struct timeval	init;

	i = 0;
	gettimeofday(&init, NULL);
	data->start_time = init.tv_usec;
	while (i < data->philos_num)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, routine, (void *)&data->philos[i]) != 0)
		 	handle_error(THREAD_CREATE);
		i++;
	}
    if (pthread_create(monitoring, NULL, start_monitor, (void *)data));
        handle_error(THREAD_CREATE);
}

void    start(t_data *data)
{
    pthread_t monitoring;
    
    start_threads(data, &monitoring)
}
