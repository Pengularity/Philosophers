/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:46:20 by pengu             #+#    #+#             */
/*   Updated: 2023/10/03 14:55:29 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_philo_and_forks(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->simulation->print_mutex, NULL);

	i = 0;
	while (i < data->simulation->philo_nb)
	{
		pthread_mutex_init(&data->simulation->forks[i], NULL);
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = &data->simulation->forks[i];
		data->philo[i].right_fork = &data->simulation->forks[(i + 1)
			% data->simulation->philo_nb];
		gettimeofday(&data->philo[i].last_time_ate, NULL);
		data->philo[i].times_eaten = 0;
		i++;
	}
}
