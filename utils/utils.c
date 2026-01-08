/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:03:12 by yohanafi          #+#    #+#             */
/*   Updated: 2026/01/08 16:09:30 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philopher.h"

long	get_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000L + tv.tv_usec);
}

void	print_state(t_philo *philo, char *msg)
{
	long	timestamp;

	if (!msg)
		return ;
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

void	free_data(t_data *data, int i)
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

void	philo_think(t_philo *philo)
{
	print_state(philo, "is thinking");
}
