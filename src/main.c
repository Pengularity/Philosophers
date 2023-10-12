/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:57:27 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/12 04:36:59 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	t_data		*data;
	pthread_t	*philosophers;
	pthread_t	monitor_thread;

	if (ac < 5 || ac > 6)
		return (ft_error(" Invalid numbers of arguments"));
	data = init_data_structure(ft_atoi(av[1]));
	if (!data)
		return (ft_error("Initialize failure"));
	if (!parse_args(ac, av, data))
		return (cleanup(data, NULL), (ft_error("Parsing Failure")));
	if (pthread_create(&monitor_thread, NULL, monitoring, data) != 0)
		return (cleanup(data, NULL),
			ft_error("Error creating the monitoring thread"));
	philosophers = create_philosophers(data);
	if (!philosophers)
		return (cleanup(data, NULL),
			ft_error("Error creating philosopher threads"));
	wait_for_philosophers(philosophers, data->config->philo_nb);
	pthread_join(monitor_thread, NULL);
	cleanup(data, philosophers);
	return (0);
}
