/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:53:22 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/24 15:12:04 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void handle_error(char *err)
{
	printf("%s\n", err);
	exit(EXIT_FAILURE);
}

int	verify_args(t_data *data, char *meal_num)
{
	if (data->philos_num < 1)
		handle_error(PHILOS_NUM);
	if (data-> die_time < 60)
		handle_error(DIE_TIME);
	if (data->eat_time < 60)
		handle_error(EAT_TIME);
	if (data->sleep_time < 60)
		handle_error(SLEEP_TIME);
	if (meal_num && data->meal_num < 1)
		handle_error(MEAL_NUM);
	return (1);
}

int	main(int ac, char *av[])
{
	t_philo	*philos;

	if (ac < 5 || ac > 6)
		handle_error(ARGS);
	else
	{
		philos = init(av);
		start(philos);
	}
	return (0);
}
