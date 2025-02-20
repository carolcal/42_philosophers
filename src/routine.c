#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork->state);
		print_action(philo, FORK);
		pthread_mutex_lock(philo->r_fork->state);
		print_action(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork->state);
		print_action(philo, FORK);
		pthread_mutex_lock(philo->l_fork->state);
		print_action(philo, FORK);
	}
	//pegar garfos se nao estiverem travados pelo mutex
	//ao pegar, travar pelo mutex

}
void	eat(t_philo *philo, useconds_t eat_time)
{
	take_forks(philo);
	pthread_mutex_lock(philo->state);
	philo->last_meal = get_time();
	print_action(philo, EAT);
	philo->meals++;
	pthread_mutex_unlock(philo->state);
	usleep(eat_time);
	pthread_mutex_unlock(philo->l_fork->state);
	pthread_mutex_unlock(philo->r_fork->state);
}

void	sleep(t_philo *philo, useconds_t sleep_time)
{
	//pegar tempo
	print_action(philo, SLEEP);
	usleep(sleep_time);
}

void	think(t_philo *philo)
{
	//pegar tempo
	print_action(philo, THINK);
	//pensar por até comer de novo ou morrer
}

void	*routine(t_data *data)
{
	while (!stop(data))
    {
        eat(data->philo, data->eat_time);
        sleep(data->philo, data->sleep_time);
        think(data->philo);
    }
}