/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:29:29 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/25 16:07:15 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <stdatomic.h>

# define BOLD_BLACK   "\033[1;30m"
# define BOLD_RED     "\033[1;31m"
# define BOLD_GREEN   "\033[1;32m"
# define BOLD_YELLOW  "\033[1;33m"
# define BOLD_BLUE    "\033[1;34m"
# define BOLD_MAGENTA "\033[1;35m"
# define BOLD_CYAN    "\033[1;36m"
# define BOLD_WHITE   "\033[1;37m"
# define RST	"\033[0m"

typedef struct s_philo
{
	int				id;
	long			last_eat;
	int				nbr_eat;
	int				left_fork;
	int				right_fork;
	int				verif;
	pthread_t		thread;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
	int				nb_philo;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	int				nb_of_time;
	int				dead;
	atomic_int		eat_en;
	int				all_eat;
	time_t			start_time;
	t_philo			*philo;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_full;
	pthread_mutex_t	*fork;
}			t_data;

////----- ROUTINE ------////
void		*routine(void *phil);
void		eat(t_philo *philo, int id);
int			only_one(t_data *data);
void		*only_one_2(void *phil);

////----- DESTROY ------////
void		destroy_all(t_data *data);
void		destroy_fork(t_data *data, int f, int id);

////----- UTILS ------////
long long	ft_atol(char *av);
void		error_exit(char *str);
void		*safe_malloc(size_t bytes);
void		ft_join(t_data *data);
void		print(int id, t_data *data, char *msg);
void		ft_sleep(t_data *data, time_t end);
int			str_cmp(char *s1, char *s2);
int			check_value(char **argv);
time_t		get_time(t_data *data);

#endif