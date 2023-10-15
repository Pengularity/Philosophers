/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 02:21:32 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/15 21:16:46 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_simulation(t_data *data, pthread_t *philosophers)
{
	int	i;

	i = 0;
	if (data->simulation->forks)
	{
		while (i < data->config->philo_nb)
		{
			pthread_mutex_destroy(&data->simulation->forks[i]);
			if (philosophers)
				pthread_join(philosophers[i], NULL);
			i++;
		}
		free(data->simulation->forks);
	}
	free(data->simulation);
	free(data->philo);
	free(philosophers);
}

void	cleanup(t_data *data, pthread_t *philosophers)
{
	if (!data)
		return ;
	if (data->simulation)
	{
		// pthread_mutex_destroy(&data->simulation->print_mutex);
		// pthread_mutex_destroy(&data->simulation->status_mutex);
		pthread_mutex_destroy(&data->philo->times_eaten_mutex);
		pthread_mutex_destroy(&data->philo->last_time_ate_mutex);
		pthread_mutex_destroy(&data->simulation->ate_enough_mutex);
		pthread_mutex_destroy(&data->simulation->dead_mutex);
		free_simulation(data, philosophers);
	}
	free(data);
}
