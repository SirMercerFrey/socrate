#include "philosophers.h"

/*void	*philo_routine(void *philo_ptr)
{
	t_philo		*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->table->philo_nbr == 1)
	{
		only_one_philo(philo);
		return (NULL);
	}
	while (simulation_running(philo))
	{
		eat(philo);
		if (check_meal(philo) || !simulation_running(philo))
			break ;
		sleepx(philo);
		if (!simulation_running(philo))
			break ;
		think(philo);
	}
	return (NULL);
}*/

void	*philo_routine(void *philo_ptr)
{
	t_philo		*philo;
	long		now;

	philo = (t_philo *)philo_ptr;
	if (philo->table->philo_nbr == 1)
	{
		only_one_philo(philo);
		return (NULL);
	}
	while (simulation_running(philo))
	{
		now = now_ms();
		eat(philo, now);
		if (check_meal(philo) || !simulation_running(philo))
			break ;
		now = now_ms();
		sleepx(philo, now);
		if (!simulation_running(philo))
			break ;
		now = now_ms();
		think(philo, now);
	}
	return (NULL);
}	

/*void	eat(t_philo *philo)
{
	long	meal_time;

	pthread_mutex_lock(philo->left_fork);
	if (!simulation_running(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_fork(philo);
	pthread_mutex_lock(philo->right_fork);
	if (!simulation_running(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	print_fork(philo);
	meal_time = timestamp_from_start(philo);
	print_meal(philo, meal_time);
	pthread_mutex_lock(&philo->table->death_lock);
	philo->last_meal_time = meal_time;
	pthread_mutex_unlock(&philo->table->death_lock);
	ft_sleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->meal_lock);
	++philo->meals_eaten;
	pthread_mutex_unlock(&philo->table->meal_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}*/

void	eat(t_philo *philo, long now)
{
	long	meal_time;

	pthread_mutex_lock(philo->left_fork);
	if (!simulation_running(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_fork(philo, now);
	pthread_mutex_lock(philo->right_fork);
	if (!simulation_running(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	print_fork(philo, now);
	meal_time = timestamp_from_start(philo);
	print_meal(philo, meal_time);
	pthread_mutex_lock(&philo->table->death_lock);
	philo->last_meal_time = meal_time;
	pthread_mutex_unlock(&philo->table->death_lock);
	ft_sleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->meal_lock);
	++philo->meals_eaten;
	pthread_mutex_unlock(&philo->table->meal_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}	

/*void	sleepx(t_philo *philo)
{
	print_sleep(philo);
	ft_sleep(philo->table->time_to_sleep);
}*/

void	sleepx(t_philo *philo, long now)
{
	(void)now;

	print_sleep(philo, now);
	ft_sleep(philo->table->time_to_sleep);
}

/*void	think(t_philo *philo)
{
	print_think(philo);
	if (philo->id % 2 == 0)
	{
	//	ft_sleep(philo->table->time_to_eat / 2);
		usleep(1500);
	}
}*/

void	think(t_philo *philo, long now)
{
	(void)now;

	print_think(philo, now);
	if (philo->id % 2 == 0)
		usleep(1500);
}

/*int		simulation_running(t_philo *philo)
{
	int		running;

	pthread_mutex_lock(&philo->table->death_lock);
	running = !philo->table->stop_simulation;
	pthread_mutex_unlock(&philo->table->death_lock);
	return (running);
}*/

int			simulation_running(t_philo *philo)
{
	return (!philo->table->stop_simulation);
}

int		check_meal(t_philo *philo)
{
	int		sated;

	if (philo->table->meals_required == -1)
		return (0);
	pthread_mutex_lock(&philo->table->meal_lock);
	if (philo->meals_eaten < philo->table->meals_required)
		sated = 0;
	else
		sated = 1;
	pthread_mutex_unlock(&philo->table->meal_lock);
	return (sated);
}

void	only_one_philo(t_philo *philo)
{
	long	now;

	pthread_mutex_lock(philo->left_fork);
	now = now_ms();
	print_fork(philo, now);
	pthread_mutex_unlock(philo->left_fork);
	ft_sleep(philo->table->time_to_die);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld\t%d died\n", timestamp_from_start(philo), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	set_end_simulation(philo);
}
