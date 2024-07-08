/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:55 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/08 15:38:55 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(const char *str)
{
	long	rlt;
	char	sign;

	rlt = 0;
	sign = 1;
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

static void	init_philo(t_data *data)
{

}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	data = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Error: Try with 5 or 6 arg"));
	data.nbr_philo = ft_atol(argv[1]);
	data.time_to_die = ft_atol(argv[2]);
	data.time_to_eat = ft_atol(argv[3]);
	data.time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data.nbr_eat = ft_atol(argv[5]);
	else
		data.nbr_eat = -1;
	init_philo(&data);
	return (0);
}
