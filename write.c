/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:10:06 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/16 14:29:02 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_status_debug(t_status_philo status, t_philo *philo, long elsaped)
{
	if (TAKE_FIRST_FORK == status && !simulation_finished(philo->data))
		printf(BOLD_WHITE"%-6ld"RST"%d has takken fork n'1 Y\n", elsaped, philo->id);
	else if (TAKE_SECOND_FORK == status && !simulation_finished(philo->data))
		printf(BOLD_WHITE"%-6ld"RST"%d has takken fork n'2 Y\n", elsaped, philo->id);
	else if (EATING == status && !simulation_finished(philo->data))
		printf(BOLD_WHITE"%-6ld"RST"%d eating :D\n", elsaped, philo->id);
	else if (SLEEPING == status && !simulation_finished(philo->data))
		printf(BOLD_WHITE"%-6ld"RST"%d sleeping zzz\n", elsaped, philo->id);
	else if (THINKING == status && !simulation_finished(philo->data))
		printf(BOLD_WHITE"%-6ld"RST"%d thinking ^^\n", elsaped, philo->id);
	else if (DIED == status)
		printf(BOLD_RED"%-6ld%d died X/ rip\n"RST, elsaped, philo->id);
}

void	write_status(t_status_philo status, t_philo *philo, bool debug)
{
	long	elsaped;

	elsaped = gettime(MILISECONDS);
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->data->write_mutex, LOCK);
	if (debug)
		write_status_debug(status, philo, elsaped);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status) && 
			!simulation_finished(philo->data))
			printf(BOLD_WHITE"%-6ld"RST"%d has takken fork YY\n", elsaped, philo->id);
		else if (EATING == status && !simulation_finished(philo->data))
			printf(BOLD_WHITE"%-6ld"RST" %d EATING :D\n", elsaped, philo->id);
		else if (SLEEPING == status && !simulation_finished(philo->data))
			printf(BOLD_WHITE"%-6ld"RST" %d SLEEPING ZZZ\n",elsaped, philo->id);
		else if (THINKING == status && !simulation_finished(philo->data))
			printf(BOLD_WHITE"%-6ld"RST" %d THINKING ^^\n", elsaped, philo->id);
		else if (DIED == status)
			printf(BOLD_RED"%-6ld %d DIED X/ RIP\n"RST, elsaped, philo->id);
	}	
	safe_mutex_handle(&philo->data->write_mutex, UNLOCK);
}
