/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:58:03 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/07 18:39:00 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

pthread_t	*create_philosophers(t_data *data)
{
	int			i;
	pthread_t	*philosophers;

	i = 0;
	philosophers = malloc(data->simulation->philo_nb * sizeof(pthread_t));
	if (!philosophers)
		return (ft_error("Malloc returned NULL"));
	while (i < data->simulation->philo_nb)
	{
		pthread_create(&philosophers[i], NULL, philosopher_routine, &data[i]);
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
