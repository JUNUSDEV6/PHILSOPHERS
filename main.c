/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:48:59 by yohanafi          #+#    #+#             */
/*   Updated: 2026/01/08 18:07:48 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philopher.h"

static int	parsing(t_data *data, char **argv)
{
	data->simulation_f = false;
	data->threads_ready = false;
	data->table_mtx_flag = false;
	data->write_mtx_flag = false;
	data->philo = NULL;
	data->forks = NULL;
	data->nbr_philo = ft_atol(argv[1]);
	if (data->nbr_philo > 500)
	{
		printf("max 500 philos");
		return (-1);
	}
	data->t_t_die = ft_atol(argv[2]) * 1000;
	data->t_t_eat = ft_atol(argv[3]) * 1000;
	data->t_t_sleep = ft_atol(argv[4]) * 1000;
	if (data->nbr_philo <= 0 || data->t_t_die <= 0
		|| data->t_t_eat <= 0 || data->t_t_sleep <= 0)
		return (-1);
	data->nbr_meal = -1;
	if (argv[5])
		data->nbr_meal = ft_atol(argv[5]);
	return (0);
}

static int	init_data(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->nbr_philo);
	if (!data->philo)
		return (-1);
	if (pthread_mutex_init(&data->table_mtx, NULL) == 0)
		data->table_mtx_flag = true;
	if (pthread_mutex_init(&data->write_mtx, NULL) == 0)
		data->write_mtx_flag = true;
	if (!data->table_mtx_flag || !data->write_mtx_flag)
		return (-1);
	data->forks = malloc(sizeof(t_fork) * data->nbr_philo);
	if (!data->forks)
		return (-1);
	i = -1;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->forks[i].fork_id = i;
	}
	return (0);
}

static void	init_philo(t_data *data)
{
	int	i;

	data->time_start = get_time_us();
	i = -1;
	while (++i < data->nbr_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].nbr_meal_eat = 0;
		data->philo[i].last_meal = data->time_start;
		data->philo[i].full = false;
		pthread_mutex_init(&data->philo[i].philo_mutex, NULL);
		data->philo[i].first_fork = &data->forks[i];
		if (data->nbr_philo > 1)
			data->philo[i].second_fork
				= &data->forks[(i + 1) % data->nbr_philo];
		data->philo[i].data = data;
	}
}

static void	monitor_philos(t_data *data, int i, long now)
{
	while (!data->simulation_f)
	{
		i = -1;
		while (++i < data->nbr_philo)
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
					printf("%ld %d died\n", (now - data->time_start) / 1000,
						data->philo[i].id);
				}
				pthread_mutex_unlock(&data->write_mtx);
				return ;
			}
			pthread_mutex_unlock(&data->philo[i].philo_mutex);
		}
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = -1;
	if (argc < 5 || argc > 6)
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (parsing(data, argv) == -1 || init_data(data) == -1)
	{
		free_data(data, -1);
		return (1);
	}
	init_philo(data);
	while (++i < data->nbr_philo)
		pthread_create(&data->philo[i].thread_id, NULL, philo_routine,
			&data->philo[i]);
	data->threads_ready = true;
	monitor_philos(data, -1, 0);
	i = -1;
	while (++i < data->nbr_philo)
		pthread_join(data->philo[i].thread_id, NULL);
	free_data(data, -1);
	return (0);
}
