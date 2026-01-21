
#include "include/philopher.h"

static int	check_philosopher_death(t_data *data, int i, long now)
{
	pthread_mutex_lock(&data->philo[i].philo_mutex);
	now = get_time_us();
	if (now - data->philo[i].last_meal > data->t_t_die)
	{
		pthread_mutex_unlock(&data->philo[i].philo_mutex);
		pthread_mutex_lock(&data->write_mtx);
		if (!data->simulation_f)
		{
			data->simulation_f = true;
			printf("%ld %d died\n", (now - data->time_start)
				/ 1000, data->philo[i].id);
		}
		pthread_mutex_unlock(&data->write_mtx);
		return (1);
	}
	pthread_mutex_unlock(&data->philo[i].philo_mutex);
	return (0);
}

static int	check_all_full(t_data *data, int full_count)
{
	if (data->nbr_meal != -1 && full_count == data->nbr_philo)
	{
		pthread_mutex_lock(&data->write_mtx);
		data->simulation_f = true;
		pthread_mutex_unlock(&data->write_mtx);
		return (1);
	}
	return (0);
}

void	monitor_philos(t_data *data, int i, int full_count, long now)
{
	while (!data->simulation_f)
	{
		i = -1;
		full_count = 0;
		while (++i < data->nbr_philo)
		{
			pthread_mutex_lock(&data->philo[i].philo_mutex);
			if (data->philo[i].full)
			{
				full_count++;
				pthread_mutex_unlock(&data->philo[i].philo_mutex);
			}
			else
			{
				pthread_mutex_unlock(&data->philo[i].philo_mutex);
				if (check_philosopher_death(data, i, now))
					return ;
			}
		}
		if (check_all_full(data, full_count))
			return ;
		usleep(1000);
	}
}
