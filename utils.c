/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:29:01 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/16 15:32:25 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimoefday failed");
	if (SECONDS == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILISECONDS == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECONDS == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("wrong imput to gettime!");
	return (1337);
}

void	precise_usleep(long usec, t_data *data)
{
	long	start;
	long	elsaped;
	long	rem;

	start = gettime(MICROSECONDS);
	while (gettime(MICROSECONDS) - start < usec)
	{
		if (simulation_finished(data))
			break ;
		elsaped = gettime(MICROSECONDS) - start;
		rem = usec - elsaped;
		if (rem > 1e3)
			usleep(usec / 2);
		else
		{
			while (gettime(MICROSECONDS) - start < usec)
				;
		}
	}
}

void	error_exit(char *str)
{
	printf(BOLD_RED"%s"RST, str);
	exit(EXIT_FAILURE);
}

static inline bool is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool is_space(char c)
{
	return((c >= 9 && c <= 13) || c == 32);
}

static const char	*valid_input(const char *str)
{
	const char	*number;
	int			leng;

	leng = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		str++;
	else if (*str == '-')
		error_exit("!!! only positif number zeubi !!!\n");
	if (!is_digit(*str))
		error_exit("!!! only number zeubi !!!\n");
	number = str;
	while (is_digit(*str++))
		++leng;
	if (leng > 10)
		error_exit("!!! value too big, INT_MAX is the limit !!!\n");
	return (number);
}

long	ft_atol(const char *str)
{
	long	rlt;
	char	sign;

	rlt = 0;
	sign = 1;
	str = valid_input(str);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		rlt = rlt * 10 + *str - 48;
		str++;
	}
	return (rlt * sign);
}
