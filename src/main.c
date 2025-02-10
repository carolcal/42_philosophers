/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:53:22 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/10 17:59:21 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void handle_error(char *err)
{
	ft_printf("%s\n", err);
	exit(EXIT_FAILURE);
}

int	main(int ac, char *av[])
{
	if (ac < 5 || ac > 6)
		handle_error(ARGS);
	else
		ft_printf("%s", av[4]);
	return (0);
}
