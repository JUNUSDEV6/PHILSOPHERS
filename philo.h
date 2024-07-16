/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:14:58 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/16 14:59:44 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>

#define BOLD_BLACK   "\033[1;30m"
#define BOLD_RED     "\033[1;31m"
#define BOLD_GREEN   "\033[1;32m"
#define BOLD_YELLOW  "\033[1;33m"
#define BOLD_BLUE    "\033[1;34m"
#define BOLD_MAGENTA "\033[1;35m"
#define BOLD_CYAN    "\033[1;36m"
#define BOLD_WHITE   "\033[1;37m"
#define RST        "\033[0m"

#define DEBUG_MODE 0

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

typedef enum e_time_code
{
	SECONDS,
	MILISECONDS,
	MICROSECONDS,
}			t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
	EINVAL,
	EDEADLK,
	EPERM,
	ENOMEM,
	EBUSY,
	EAGAIN,
	ESRCH,
}			t_status_philo;

typedef	pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

typedef struct s_data t_data;

typedef struct	s_philo
{
	unsigned int	id;
	long			meals_eat;
	long			last_meal_time;
	bool			full;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	t_mtx			philo_mutex;
	t_data			*data;
}		t_philo;

struct	s_data
{
	long	nbr_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_eat;
	long	start_time;
	bool	end_simulation;
	bool	all_threads_ready;
	t_mtx	table_mutex;
	t_mtx	write_mutex;
	t_fork	*forks;
	t_philo	*philo;
};

//dinners_simulations
void	dinner_start(t_data *data);
void	*dinner_similuation(void *data);
void	write_status(t_status_philo status, t_philo *philo, bool debug);

//synchro
void	wait_the_threads(t_data *data);
//safe_fucntions
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), 
		void *data, t_opcode opcode);

//setters_getters
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	simulation_finished(t_data *data);
//utils
void	precise_usleep(long usec, t_data *data);
long	gettime(t_time_code time_code);
void	error_exit(char *str);
long	ft_atol(const char *str);

#endif 