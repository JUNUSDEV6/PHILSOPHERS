/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:30:32 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/25 16:07:31 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(char *str)
{
	printf(BOLD_RED"%s"RST, str);
	exit(EXIT_FAILURE);
}

static int	is_digit(char **av)
{
	int	i;
	int	j;

	i = -1;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < 48 || av[i][j] > 57)
				return (1);
	}
	return (0);
}

long long	ft_atol(char *av)
{
	int			sign;
	long long	nbr;

	sign = 0;
	nbr = 0;
	while ((*av >= 9 && *av <= 13) || *av == 32)
		av++;
	if (*av == 45 || *av == 43)
	{
		if (*av == 45)
			sign++;
		av++;
	}
	while (*av >= 48 && *av <= 57)
	{
		nbr = (nbr * 10) + (*av - 48);
		av++;
	}
	if ((sign % 2) > 0)
		nbr = -nbr;
	return (nbr);
}

int	check_value(char **argv)
{
	int	i;

	i = -1;
	if (is_digit(argv))
		return (1);
	while (argv[++i])
		if (ft_atol(argv[i]) > INT_MAX || !ft_atol(argv[i])
			|| ft_atol(argv[i]) < 0)
			return (1);
	return (0);
}

time_t	get_time(t_data *data)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - data->start_time);
}
