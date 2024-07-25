/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:30:16 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/25 15:58:33 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_dead(t_data *data)
{
	int	i;

	while (data->dead != 1 && data->eat_en <= data->nb_philo)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (data->nb_philo == data->eat_en)
				return ;
			if ((get_time(data) - data->philo[i].last_eat) > data->t_to_die)
			{
				pthread_mutex_lock(&data->m_dead);
				print(data->philo[i].id, data, BOLD_RED"DEAD");
				data->dead = 1;
				pthread_mutex_unlock(&data->m_dead);
				return ;
			}
		}
	}
	return ;
}

static int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->philo = safe_malloc(sizeof(t_philo) * data->nb_philo);
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].nbr_eat = 0;
		data->philo[i].left_fork = i;
		data->philo[i].verif = 0;
		if (data->nb_philo > 1)
			data->philo[i].right_fork = (i + 1) % data->nb_philo;
		data->philo[i].data = data;
	}
	data->start_time = get_time(data);
	return (0);
}

static int	init_fork(t_data *data)
{
	int	i;

	i = -1;
	data->fork = safe_malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	while (++i < data->nb_philo)
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (destroy_fork(data, i, 0), 1);
	if (pthread_mutex_init(&(data->m_print), NULL))
		return (destroy_fork(data, data->nb_philo, 0), 1);
	if (pthread_mutex_init(&(data->m_dead), NULL))
		return (destroy_fork(data, data->nb_philo, 0), 1);
	data->dead = 0;
	return (0);
}

static int	init_value(t_data *data, char **argv, int argc)
{
	data->nb_philo = ft_atol(argv[1]);
	if (data->nb_philo > 200)
		error_exit("!!! MAX 200 philos !!!");
	data->t_to_die = ft_atol(argv[2]);
	data->t_to_eat = ft_atol(argv[3]);
	data->t_to_sleep = ft_atol(argv[4]);
	data->nb_of_time = -1;
	if (argc == 6)
		data->nb_of_time = ft_atol(argv[5]);
	data->dead = 0;
	data->eat_en = 0;
	data->philo = NULL;
	data->start_time = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc > 6 || argc < 5)
		return (error_exit("!!! its 5 or 6 arg !!!"), 1);
	if (check_value(argv + 1) || init_value(&data, argv, argc))
		return (error_exit("only digit positif < INT_MAX"), 1);
	if (init_fork(&data))
		return (error_exit("!!! ERROR: INIT_FORK !!!"), 1);
	if (init_philo(&data))
		return (error_exit("!!! ERROR: INIT_PHILO !!!"), 1);
	i = -1;
	if (data.nb_philo == 1)
		return (only_one(&data));
	else
	{
		while (++i < data.nb_philo)
			if (pthread_create(&data.philo[i].thread, NULL,
					routine, (void *)&data.philo[i]))
				return (destroy_all(&data), 1);
	}
	ft_sleep(&data, 10);
	is_dead(&data);
	ft_join(&data);
	return (destroy_all(&data), 0);
}
