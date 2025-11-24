#include "philosophers.h"

/*void	print_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld\t%d has taken a fork\n", timestamp_from_start(philo), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}*/

void	print_fork(t_philo *philo, long now)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld\t%d has taken a fork\n", now - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}


void	print_meal(t_philo *philo, long meal_time)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld\t%d is eating\n", meal_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

/*void	print_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld\t%d is sleeping\n", timestamp_from_start(philo), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}*/

void	print_sleep(t_philo *philo, long now)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld\t%d is sleeping\n", now - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

/*void	print_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld\t%d is thinking\n", timestamp_from_start(philo), philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}*/

void	print_think(t_philo *philo, long now)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld\t%d is thinking\n", now - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}



