/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:30:32 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/23 12:18:17 by yohanafi         ###   ########.fr       */
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
		if (argv[i] > INT_MAX || !ft_atol(argv[i]))
			return (1);
	return (0);
}