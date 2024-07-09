/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohanafi <yohanafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:06:55 by yohanafi          #+#    #+#             */
/*   Updated: 2024/07/09 12:13:30 by yohanafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	parse_input(t_data *data, char **argv)
{
	data->nbr_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);

}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	data = NULL;
	if (argc < 5 || argc > 6)
		error_exit("wrong input:\n"BOLD_GREEN"Correct is ./philo 5 800 200 200 [5]"RST);
	parse_input(&data, argv);
	if (argc == 6)
		data.nbr_eat = ft_atol(argv[5]);
	else
		data.nbr_eat = -1;
	init_philo(&data);
	return (0);
}
