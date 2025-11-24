#include "philosophers.h"

void	monitor_philos(t_philo *philos)
{
	int		deadman;

	while (simulation_running(philos))
	{
		if (check_philos_meals(philos))
		{
			set_end_simulation(philos);
			printf("J'ai bien mange et j'ai bien bu, merci petit Jesus\n");
			return ;
		}
		deadman = check_philos_death(philos);
		if (deadman)
		{
			set_end_simulation(philos);
			printf("%ld\t%d died\n", timestamp_from_start(&philos[deadman - 1]), deadman);
			return ;
		}
		ft_sleep(1);
	}
}

int		check_philos_meals(t_philo *philos)
{
	int		i;
	int		sated;
	int		philo_fulled;

	if (philos[0].table->meals_required == -1)
		return (0);
	philo_fulled = 0;
	i = 0;
	while (i < philos[0].table->philo_nbr)
	{
		pthread_mutex_lock(&philos[0].table->meal_lock);
		if (philos[i].meals_eaten < philos->table->meals_required)
			sated = 0;
		else
			sated = 1;
		pthread_mutex_unlock(&philos[0].table->meal_lock);
		if (sated)
			++philo_fulled;
		++i;
	}
	if (philo_fulled == philos[0].table->philo_nbr)
		return (1);
	return (0);
}

int		check_philos_death(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < philos[0].table->philo_nbr)
	{
		if (!philo_sated(&philos[i]))
		{
			if (philo_starving(&philos[i]))
				return (philos[i].id);
		}
		++i;
	}
	return (0);
}

int		philo_sated(t_philo *philo)
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

int		philo_starving(t_philo *philo)
{
	int			dead;
	long		current_time;

	pthread_mutex_lock(&philo->table->death_lock);
	current_time = timestamp_from_start(philo); 
	if (philo->table->time_to_die < current_time - philo->last_meal_time)
		dead = 1;
	else
		dead = 0;
	pthread_mutex_unlock(&philo->table->death_lock);
	return (dead);
}
