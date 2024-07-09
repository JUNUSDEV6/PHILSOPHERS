/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:14:58 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/09 11:23:36 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
#define	PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limit.h>

typedef	pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

struct	s_philo
{
	unsigned int	id;
	long			meals_eat;
	long			last_meal_time;
	bool			full;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	struct s_data	*data;
}				t_philo;

typedef	struct	s_data
{
	long	nbr_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_eat;
	long	start_time;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philo;
}				t_data;

