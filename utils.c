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
		usleep(200);
}

void	set_end_simulation(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->death_lock);
	philo->table->stop_simulation = 1;
	pthread_mutex_unlock(&philo->table->death_lock);
}

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	sign = 1;
	while (*str && is_space(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		++str;
	}
	return (sign * result);
}

long	ft_atol(char *str)
{
	long	result;
	int		sign;

	sign = 1;
	while (*str && is_space(*str))
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		++str;
	}
	return (sign * result);
}
