/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:03:37 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/16 15:37:54 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void thinking(t_philo *philo)
{
	write_status(THINKING, philo, DEBUG_MODE);
}


static void eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILISECONDS));
	philo->meals_eat++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->nbr_eat > 0 && philo->meals_eat == philo->data->nbr_eat)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
	
}

void	*dinner_similuation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_the_threads(philo->data);
	while (!simulation_finished(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, debug);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	if (0 == data->nbr_eat)
		return ;
	else if (1 == data->nbr_philo)
		safe_thread_handle(&data->philo[0].thread_id, only_one_philo, &data->philo[i], CREATE)
	else
	{
		while (i++ < data->nbr_philo)
			safe_thread_handle(&data->philo[i].thread_id, dinner_similuation,
				&data->philo[i], CREATE);
	}
	data->start_time = gettime(MILISECONDS);
	set_bool(&data->table_mutex, &data->all_threads_ready, true);
	i = -1;
	while (++i < data->nbr_philo)
		safe_thread_handle(&data->philo[i].thread_id, NULL, NULL, JOIN);
}
