/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:03:37 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/15 14:02:27 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner_similuation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_the_threads(philo->data);
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	if (0 == data->nbr_eat)
		return ;
	else if (1 == data->nbr_philo)

	else
	{
		while (i++ < data->nbr_philo)
			safe_thread_handle(&data->philo[i].thread_id, dinner_similuation,
				&data->philo_nbr[i], CREATE);
	}
	set_bool(&data->table_mutex, &table->all_threads_ready, true);
}
