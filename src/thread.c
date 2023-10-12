/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:58:03 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/12 05:17:31 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

pthread_t	*create_philosophers(t_data *data)
{
	int			i;
	pthread_t	*philosophers;
	t_data		*data_copy;

	i = 0;
	philosophers = malloc(data->config->philo_nb * sizeof(pthread_t));
	if (!philosophers)
		return (ft_error("Malloc faillure"), NULL);
	while (i < data->config->philo_nb)
	{
		data_copy = malloc(sizeof(t_data));
		*data_copy = *data;
		data_copy->philo = &data->philo[i];
		pthread_create(&philosophers[i], NULL, philosopher_routine, data_copy);
		printf("Thread for philosopher %d created\n", i + 1);
		i++;
	}
	return (philosophers);
}

void	wait_for_philosophers(pthread_t *philosophers, int philo_nb)
{
	int	i;

	i = 0;
	while (i < philo_nb)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
}
