/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:10:06 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/15 17:34:37 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_status_philo status, t_philo *philo, bool debug)
{
	long	elsaped;

	elsaped = gettime(MILISECONDS);
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->data->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elsaped)
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_STATUS == status) && 
			!simulation_finished(philo->data))
			printf(W"%-6ld"RST" %d has takken fork YY\n");
		else if (EATING == status && !simulation_finished(philo->data))
			printf(W"%-6ld"RST" %d EATING :D\n");
		else if (SLEEPING == status && !simulation_finished(philo->data))
			printf(W"%-6ld"RST" %d SLEEPING ZZZ\n");
		else if (THIKING == status && !simulation_finished(philo->data))
			printf(W"%-6ld"RST" %d THINKING ^^\n");
		else if (DIED == status)
			printf(W"%-6ld"RST" %d DIED X/ RIP\n");
	}	
	safe_mutex_handle(&philo->data->write_mutex, UNLOCK);
}
