/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:20:23 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/25 16:09:31 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*only_one_2(void *phil)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)phil;
	data = philo->data;
	pthread_mutex_lock(&data->fork[0]);
	print(1, data, BOLD_GREEN"has taken a fork"RST);
	ft_sleep(data, data->t_to_die);
	print(1, data, BOLD_RED"is dead"RST);
	pthread_mutex_unlock(&data->fork[0]);
	destroy_all(data);
	return (NULL);
}

int	only_one(t_data *data)
{
	if (pthread_create(&data->philo[0].thread, NULL, only_one_2,
			(void *)&data->philo[0]))
		return (destroy_all(data), 1);
	ft_sleep(data, data->t_to_die);
	pthread_join(data->philo[0].thread, NULL);
	return (0);
}

void	eat(t_philo *philo, int id)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->fork[philo->left_fork]);
	print(philo->id, data, BOLD_GREEN"has taken fork"RST);
	pthread_mutex_lock(&data->fork[philo->right_fork]);
	print(philo->id, data, BOLD_GREEN"has taken fork"RST);
	print(philo->id, data, BOLD_MAGENTA"is eating"RST);
	data->philo[id].nbr_eat++;
	ft_sleep(data, data->t_to_eat);
	pthread_mutex_unlock(&(data->fork[philo->left_fork]));
	pthread_mutex_unlock(&(data->fork[philo->right_fork]));
}

void	*routine(void *phil)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)phil;
	data = philo->data;
	philo->last_eat = data->start_time;
	if (philo->id % 2 == 0)
		ft_sleep(data, 10);
	while (data->dead != 1 || data->eat_en >= data->nb_philo)
	{
		eat(philo, philo->id);
		print(philo->id, data, BOLD_CYAN"is sleeping"RST);
		ft_sleep(data, data->t_to_sleep);
		print(philo->id, data, BOLD_YELLOW"is thinking"RST);
		if (data->eat_en >= data->nb_philo)
			return (NULL);
	}
	return (NULL);
}
