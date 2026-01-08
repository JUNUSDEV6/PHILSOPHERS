
#include "../include/philopher.h"

void free_data(t_data *data, int i)
{
    if (!data)
        return ;

    if (data->philo)
    {
        i = -1;
        while (++i < data->nbr_philo)
            pthread_mutex_destroy(&data->philo[i].philo_mutex);
        free(data->philo);
    }

    if (data->forks)
    {
        i = -1;
        while (++i < data->nbr_philo)
            pthread_mutex_destroy(&data->forks[i].fork);
        free(data->forks);
    }

    if (data->table_mtx_flag)
        pthread_mutex_destroy(&data->table_mtx);
    if (data->write_mtx_flag)
        pthread_mutex_destroy(&data->write_mtx);

    free(data);
}



void    error(t_data *data, int code)
{
    if (code == 0)
        free_data(data, -1);
}