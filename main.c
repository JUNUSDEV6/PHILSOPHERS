/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:55 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/16 15:33:42 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *fork, int philo_pos)
{
	int	philo_nbr;

	philo_nbr = philo->data->nbr_philo;
	philo->first_fork = &fork[(philo_pos + 1) % philo_nbr];
	philo->second_fork = &fork[philo_pos];
	if (philo_nbr % 2 == 0)
	{
		philo->first_fork = &fork[philo_pos];
		philo->second_fork = &fork[(philo_pos + 1) % philo_nbr];
	}
}

static void	parse_input(t_data *data, char **argv)
{
	data->nbr_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1e3;
	data->time_to_eat = ft_atol(argv[3]) * 1e3;
	data->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (data->time_to_die < 6e4 ||
		data->time_to_eat < 6e4 ||
		data->time_to_sleep < 6e4)
		error_exit("use timestamps major than 60 ms :)");
	if (argv[5])
		data->nbr_eat = ft_atol(argv[5]);
	else
		data->nbr_eat = -1;
}

static void philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->nbr_philo)
	{
		philo = data->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_eat = 0;
		philo->data = data;
		safe_mutex_handle(&philo->philo_mutex, INIT);
		assign_forks(philo, data->forks, i);
	}
}

static void	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->end_simulation = false;
	data->all_threads_ready = false;
	data->philo = safe_malloc(sizeof(t_philo) * data->nbr_philo);
	safe_mutex_handle(&data->table_mutex, INIT);
	safe_mutex_handle(&data->write_mutex, INIT);
	data->forks = safe_malloc(sizeof(t_fork) * data->nbr_philo);
	while (++i < data->nbr_philo)
	{
		safe_mutex_handle(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	philo_init(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	if (argc < 5 || argc > 6)
		error_exit("wrong input:\n"BOLD_GREEN"Correct is ./philo 5 800 200 200 [5]"RST);
	parse_input(data, argv);
	data_init(data);
	//dinner(data);
	//clean(data);
	return (0);
}
