/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:10:06 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/15 17:16:02 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status_philo status, t_philo *philo)
{
	safe_mutex_handle(&philo->data->write_mutex, LOCK);
	if (TAKE_FIRST_FORK == status || TAKE_SECOND_STATUS == status)
}