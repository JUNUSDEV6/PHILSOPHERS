/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:03:37 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/09 18:16:19 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			safe_thread_handle(&data->philo[i].thread_id, )
	}
}
