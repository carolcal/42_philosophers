/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:20:57 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/12 13:53:00 by cayamash         ###   ########.fr       */
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