/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:12 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/20 17:35:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>

//Print Macros
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\033[1;31mdied\033[0m"

//Error Macros
# define ARGS "Error: Invalid number of arguments!\n"
# define PHILOS_NUM "Error: There must be at least one philosopher!\n"
# define DIE_TIME "Error: Time to Die is too low!\n"
# define EAT_TIME "Error: Time to Eat is too low!\n"
# define SLEEP_TIME "Error: Time to Sleep si too low!\n"
# define MEAL_NUM "Error: Each philosopher must do at least 1 meal!\n"
# define THREAD_CREATE "Error: When creatinh Thread!\n"
# define THREAD_JOIN "Error: When joining Thread!\n"
# define MALLOC_FAILED "Error: Failed to Malloc!\n"

//Structs
typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	int		id;
	t_mtx	state;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			meals;
	t_fork		*r_fork;
	t_fork		*l_fork;
	pthread_t	thread_id;
	t_mtx		state;
    t_data      data;
}	t_philo;

typedef struct s_data
{
	int			philos_num;
	int			meal_num;
	suseconds_t	start_time;
	useconds_t	eat_time;
	useconds_t	sleep_time;
	useconds_t	die_time;
	t_philo		*philos;
	t_fork		*forks;
    t_mtx       *print;
}	t_data;

//Functions
int		ft_atoi(const char *nptr);
void 	handle_error(char *err);
void	verify_args(t_data *data, char *meal_num);
t_data	*init_data(char *av[]);
void	start_eating(t_data *data);

#endif