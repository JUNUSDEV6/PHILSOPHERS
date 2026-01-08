/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:09:01 by yohanafi          #+#    #+#             */
/*   Updated: 2026/01/08 16:11:24 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philopher.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->second_fork->fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->first_fork->fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->first_fork->fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&philo->second_fork->fork);
		print_state(philo, "has taken a fork");
	}
}

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal = get_time_us();
	pthread_mutex_unlock(&philo->philo_mutex);
	print_state(philo, "is eating");
	usleep(philo->data->t_t_eat);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->nbr_meal_eat++;
	if (philo->data->nbr_meal != -1 && philo->nbr_meal_eat
		>= philo->data->nbr_meal)
		philo->full = true;
	pthread_mutex_unlock(&philo->philo_mutex);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

static void	philo_sleep(t_philo *philo)
{
	print_state(philo, "is sleeping");
	usleep(philo->data->t_t_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *) arg;
	data = philo->data;
	while (!data->threads_ready)
		usleep(100);
	if (philo->data->nbr_philo == 1)
	{
		pthread_mutex_lock(&philo->first_fork->fork);
		print_state(philo, "has taken a fork");
		usleep(data->t_t_die);
		pthread_mutex_unlock(&philo->first_fork->fork);
		return (NULL);
	}
	while (!data->simulation_f && !philo->full)
	{
		take_forks(philo);
		philo_eat(philo);
		drop_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
