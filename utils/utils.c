#include "../include/philopher.h"

long get_time_us(void)
{
    struct timeval	tv;

	gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000L + tv.tv_usec);
}

void    print_state(t_philo *philo, char *msg)
{
    long	timestamp;

	pthread_mutex_lock(&philo->data->write_mtx);
	if (philo->data->simulation_f == true)
	{
		pthread_mutex_unlock(&philo->data->write_mtx);
		return ;
	}
	timestamp = (get_time_us() - philo->data->time_start) / 1000;
	printf("%ld %d %s\n", timestamp, philo->id, msg);
    pthread_mutex_unlock(&philo->data->write_mtx);
}

long long	ft_atol(char *av)
{
	int			sign;
	long long	nbr;

	sign = 0;
	nbr = 0;
	while ((*av >= 9 && *av <= 13) || *av == 32)
		av++;
	if (*av == 45 || *av == 43)
	{
		if (*av == 45)
			sign++;
		av++;
	}
	while (*av >= 48 && *av <= 57)
	{
		nbr = (nbr * 10) + (*av - 48);
		av++;
	}
	if ((sign % 2) > 0)
		nbr = -nbr;
	return (nbr);
}
