/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:02:44 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/24 16:13:00 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_fork(t_data *data, int f, int id)
{
	int	i;

	i = -1;
	if (id == 1)
	{
		pthread_mutex_destroy(&data->m_print);
	}
	else
	{
		while (data->philo && ++i < f)
			pthread_mutex_destroy(&data->fork[i]);
	}
	free(data->fork);
}

void	destroy_all(t_data *data)
{
	destroy_fork(data, data->nb_philo, 1);
	free(data->philo);
}

void	*safe_malloc(size_t bytes)
{
	void	*rlt;

	rlt = malloc(bytes);
	if (!rlt)
		error_exit("Error with malloc");
	return (rlt);
}
