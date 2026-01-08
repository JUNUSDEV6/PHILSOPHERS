#include "../include/philopher.h"

void smart_sleep(long duration, t_data *data)
{
    long start;

    start = get_time_us();
    while (!data->simulation_f)
    {
        if (get_time_us() - start >= duration)
            break;
        usleep(500);
    }
}

void	philo_id(unsigned int id)
{
	if (id % 2 == 0)
		usleep(1000);
}
