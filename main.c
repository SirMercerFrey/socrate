#include "philosophers.h"

int		main(int argc, char **argv)
{
	t_table		table;
	t_philo		*philos;
	int			i;

	if (!check_args(argc, argv))
		return (1);
	if (init_table(&table, argc, argv) != 0 || init_philos(&table, &philos) != 0)
		return (1);
	i = 0;
	while (i < table.philo_nbr)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		++i;
	}
	monitor_philos(philos);
	i = 0;
	while (i < table.philo_nbr)
	{
		pthread_join(philos[i].thread, NULL);
		++i;
	}
	free_all(philos, &table);
	return (0);
}
