/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:20:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/27 12:47:15 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sin;

	num = 0;
	sin = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sin = -1;
		nptr ++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		num = (num * 10) + (*nptr - '0');
		nptr++;
	}
	return (num * sin);
}

int	get_time(void)
{
	struct timeval		init;
	static suseconds_t	init_time;
	suseconds_t			curr_time;

	gettimeofday(&init, NULL);
	if (!init_time)
	{
		init_time = (init.tv_sec * 1000) + (init.tv_usec / 1000);
		curr_time = init_time;
	}
	else
		curr_time = (init.tv_sec * 1000) + (init.tv_usec / 1000);
	return (curr_time - init_time);
}

void	print_action(t_philo *philo, char *action)
{
	int	time;

	if (!stop(philo, 0))
	{
		time = get_time();
		printf("%i philo %i %s\n", time, philo->id + 1, action);
	}
}

void	free_all(t_philo *philos)
{
	int		i;
	int		num_philos;
	t_data	*data;
	t_fork	*forks;

	i = 0;
	num_philos = philos->data->philos_num;
	data = philos->data;
	forks = data->forks;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&forks[i].state);
		pthread_mutex_destroy(&philos[i].state);
		pthread_mutex_destroy(&data->print);
		i++;
	}
	free(forks);
	free(data);
	free(philos);
}
