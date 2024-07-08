/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:14:58 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/08 14:43:57 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	struct	s_philo
{
	unsigned int	id;
	unsigned int	eat_time;
	unsigned int	die_time;
	unsigned int	thk_time;
	unsigned int	sleep_time;
	unsigned int	right_fork;
	unsigned int	left_fork;
	t_data			*data;

}				t_philo;

typedef	struct	s_data
{
	
	t_philo		*philo;
}				t_data;