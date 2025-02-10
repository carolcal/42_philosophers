/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:12 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/10 18:48:27 by cayamash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdarg.h>

//Print Macros
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\033[1;31mdied\033[0m"

//Error Macros
# define ARGS "Error: Invalid number of arguments!\n"

//Structs
typedef struct s_data
{
	int	philos_num;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	meal_num;
}	t_data;

typedef struct s_philo
{
	int	last_meal;
	int	fork1;
	int	fork2;
}	t_philo;

//Functions
void	*ft_memset(void *s, int c, size_t n);

#endif