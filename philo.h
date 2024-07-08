/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:14:58 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/08 15:41:59 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef	struct	s_philo
{
	unsigned int	id;
	
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	struct s_data	*data;
}				t_philo;

typedef	struct	s_data
{
	unsigned int	nbr_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nbr_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_lock;
	t_philo		*philo;
}				t_data;