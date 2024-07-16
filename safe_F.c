/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_F.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:08:58 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/16 15:29:31 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*rlt;

	rlt = malloc(bytes);
	if (!rlt)
		error_exit("Error with malloc");
	return (rlt);
}

static void handle_thread_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("No ressouces to creat thread");
	else if (EPERM == status)
		error_exit("The caller");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("The caller");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The caller");
	else if (ESRCH == status)
		error_exit("The caller");
	else if (EDEADLK == status)
		error_exit("The caller");	
}
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), 
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("wrong opcode for thread_handles");
}

static void handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid");
	else if (EINVAL == status && opcode == INIT)
		error_exit("The value specified by attr is invalid");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread blocked waiting for mutex");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory to create another mutex");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
	
	
}

void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("wrong opcode mutex handle");
}
