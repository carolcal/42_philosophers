/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayamash <cayamash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:16:12 by cayamash          #+#    #+#             */
/*   Updated: 2025/02/27 11:04:27 by cayamash         ###   ########.fr       */
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
# define EAT "\033[1;32mis eating\033[0m"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "\033[1;31mdied\033[0m"

//Error Macros
# define ARGS "Error: Invalid number of arguments!"
# define PHILOS_NUM "Error: There must be at least one philosopher!"
# define DIE_TIME "Error: Time to Die is too low!"
# define EAT_TIME "Error: Time to Eat is too low!"
# define SLEEP_TIME "Error: Time to Sleep si too low!"
# define MEAL_NUM "Error: Each philosopher must do at least 1 meal!"
# define THREAD_CREATE "Error: When creatinh Thread!"
# define THREAD_JOIN "Error: When joining Thread!"
# define MALLOC_FAILED "Error: Failed to Malloc!"

//Structs
typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	int		id;
	t_mtx	state;
}	t_fork;

typedef struct s_data
{
	int			philos_num;
	int			meal_num;
	int			eat_time;
	int			sleep_time;
	int			die_time;
	int			stop;
	t_fork		*forks;
	t_mtx		print;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			meals;
	t_fork		*r_fork;
	t_fork		*l_fork;
	pthread_t	thread;
	t_mtx		state;
	t_data		*data;
}	t_philo;

//main
void	handle_error(char *err);
int		verify_args(t_data *data, char *meal_num);
//utils
int		ft_atoi(const char *nptr);
int		get_time(void);
void	print_action(t_philo *philo, char *action);
void	free_all(t_philo *philos);
//init
t_philo	*init(char *av[]);
//simulation
void	start(t_philo *philos);
int		stop(t_philo *philos, int stop);
//routine
void	*routine(void *arg);
//monitor
void	*monitor(void *arg);

#endif