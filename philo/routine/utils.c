/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:28:54 by yohanafi          #+#    #+#             */
/*   Updated: 2026/01/08 17:29:50 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philopher.h"

void	smart_sleep(long duration, t_data *data)
{
	long	start;

	start = get_time_us();
	while (!data->simulation_f)
	{
		if (get_time_us() - start >= duration)
			break ;
		usleep(500);
	}
}

void	philo_id(unsigned int id)
{
	if (id % 2)
		usleep(1000);
}
