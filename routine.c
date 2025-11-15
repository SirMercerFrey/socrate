#include "philosophers.h"

void	*philo_routine(void *philo_ptr)
{
	t_philo		*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		ft_sleep(1000);
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
}

void	eat(t_philo *philo)
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
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleepx(t_philo *philo)
{
	print_sleep(philo);
	ft_sleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_think(philo);
	if (philo->id % 2 == 0)
		ft_sleep(philo->table->time_to_eat / 2);
}

int		simulation_running(t_philo *philo)
{
	int		running;

	pthread_mutex_lock(&philo->table->death_lock);
	running = !philo->table->stop_simulation;
	pthread_mutex_unlock(&philo->table->death_lock);
	return (running);
}

int		check_meal(t_philo *philo)
{
	int		sated;

	pthread_mutex_lock(&philo->table->meal_lock);
	if (philo->meals_eaten < philo->table->meals_required)
		sated = 0;
	else
		sated = 1;
	pthread_mutex_unlock(&philo->table->meal_lock);
	return (sated);
}
