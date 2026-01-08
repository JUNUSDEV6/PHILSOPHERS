/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philopher.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:11:47 by yohanafi          #+#    #+#             */
/*   Updated: 2026/01/08 16:12:33 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOPHER_H
# define PHILOPHER_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

typedef pthread_mutex_t t_mtx;

typedef struct s_data   t_data;
typedef struct s_fork   t_fork;

typedef struct s_philo
{
    unsigned int    id;
    long            nbr_meal_eat;
    long            last_meal;
    bool            full;
    pthread_t       thread_id;
    t_mtx           philo_mutex;
    t_fork          *first_fork;
    t_fork          *second_fork;
    t_data          *data;
}   t_philo;

typedef struct s_fork
{
    t_mtx           fork;
    unsigned int    fork_id;
}   t_fork;

struct s_data
{
    long    nbr_philo;
    long    t_t_eat;
    long    t_t_die;
    long    t_t_sleep;
    long    nbr_meal;
    long    time_start;
    bool    simulation_f;
    bool    threads_ready;
    t_mtx   table_mtx;
    t_mtx   write_mtx;
    bool    table_mtx_flag;
    bool    write_mtx_flag;
    t_fork  *forks;
    t_philo *philo;
};

/* Utility functions */
void        smart_sleep(long duration, t_data *data);
void	    philo_id(unsigned int id);
void	    *philo_routine(void *arg);
void        print_state(t_philo *philo, char *msg);
void        free_data(t_data *data, int i);
void		philo_think(t_philo *philo);
long        get_time_us(void);
long long	ft_atol(char *av);

#endif

