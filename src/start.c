/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:07 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/12 17:38:56 by cayamash         ###   ########.fr       */
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

void	start_eating(t_data *data)
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
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
			handle_error(THREAD_JOIN);
		i++;
	}
}

	// pthread_t p1, p2;

	// if (pthread_create(&p1, NULL, &routine, NULL) != 0)
	// 	return (1);
	// if (pthread_create(&p2, NULL, &routine, NULL) != 0)
	// 	return (2);
	// if (pthread_join(p1, NULL) != 0)
	// 	return (3);
	// if (pthread_join(p1, NULL) != 0)
	// 	return (4);