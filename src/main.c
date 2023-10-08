/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:57:27 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/08 17:25:25 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*philosophers;

	if (ac < 5 || ac > 6)
		return (ft_error(" Invalid numbers of arguments"), EXIT_FAILURE);
	data = init_data_structure(ft_atoi(av[1]));
	if (!data)
		return (ft_error("Initialize problem"), EXIT_FAILURE);
	if (!parse_args(ac, av, data))
		return (cleanup(data, NULL), EXIT_FAILURE);
	philosophers = create_philosophers(data);
	wait_for_philosophers(philosophers, data->config->philo_nb);
	return (EXIT_SUCCESS);
}
