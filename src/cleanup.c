#include "philosophers.h"

void	free_all(t_philo *philos, t_table *table)
{
	int		nbr;
	int		i;

	nbr = table->philo_nbr;
	free(philos);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->death_lock);
	pthread_mutex_destroy(&table->meal_lock);
	i = 0;
	while (i < nbr)
		pthread_mutex_destroy(&table->forks[i++]);
	free(table->forks);
}
