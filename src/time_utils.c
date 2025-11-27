#include "philosophers.h"

long	timestamp_from_start(t_philo *philo)
{
	long	start;

	start = philo->table->start_time;
	return (now_ms() - start);
}

long	now_ms(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(long ms)
{
	long	start;

	start = now_ms();
	while (now_ms() - start < ms)
		usleep(500);
}
