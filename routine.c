#include "philosophers.h"

void	*philo_routine(void *philo_ptr)
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
}

void	eat(t_philo *philo)
{
	long	meal_time;

	pthread_mutex_lock(philo->left_fork);
	if (!simulation_running(philo))
		return (pthread_mutex_unlock(philo->left_fork), (void)0);
	print_fork(philo);
	pthread_mutex_lock(philo->right_fork);
	if (!simulation_running(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_fork(philo);
	meal_time = timestamp_from_start(philo);
	print_meal(philo, meal_time);
	pthread_mutex_lock(&philo->table->death_lock);
	philo->last_meal_time = now_ms();
	pthread_mutex_unlock(&philo->table->death_lock);
	ft_sleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->table->meal_lock);
	++philo->meals_eaten;
	pthread_mutex_unlock(&philo->table->meal_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleepx(t_philo *philo)
{
	print_sleep(philo);
	ft_sleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	long	time_since_last;
	long	remaining;
	long 	nap;

	print_think(philo);
	pthread_mutex_lock(&philo->table->death_lock);
	time_since_last = now_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->table->death_lock);
	remaining = philo->table->time_to_die - time_since_last - philo->table->time_to_eat;
	if (remaining <= 0)
		return;
	nap = remaining / 10;
	if (nap < 1)
		nap = 1;
	ft_sleep(nap);
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
	pthread_mutex_lock(philo->left_fork);
	print_fork(philo);
	pthread_mutex_unlock(philo->left_fork);
	ft_sleep(philo->table->time_to_die);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld\t%d died\n", timestamp_from_start(philo), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
	set_end_simulation(philo);
}
