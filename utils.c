/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:29:01 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/09 12:42:10 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
