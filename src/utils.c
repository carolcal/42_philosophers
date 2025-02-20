/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:20:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/20 17:50:12 by marvin           ###   ########.fr       */
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

int get_time()
{
	/*
	struct timeval 
	{
		time_t		tv_sec; seconds
		suseconds_t	tv_usec; microseconds
	};
	*/
	//int gettimeofday(struct timeval *tv, struct timezone *tz);
	struct timeval time;
	
	return (gettimeofday(timeval, NULL));
}

void    print_action(t_philo *philo, char *action)
{
    int time;

    time = get_time();
	//verificar como imprimir tempo
    printf("%i %i %s", time, philo->id, action);
}