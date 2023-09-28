/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:12:24 by wnguyen           #+#    #+#             */
/*   Updated: 2023/09/29 00:21:27 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*death_monitoring(void *arg)
{
	t_data			*data;
	t_simulation	*simulation;
	long int		time_since_last_meal;

	data = (t_data *)arg;
	simulation = data->philo->simulation;

	while (simulation->status == ONGOING)
	{
		time_since_last_meal = current_time()
			- (timeval_to_millis(&data->philo->last_time_ate));
		if (time_since_last_meal > simulation->config->time_to_die)
		{
			print_status(data, "died");
			pthread_mutex_lock(&simulation->print_mutex);
			simulation->status = PHILOSOPHER_DIED;
			pthread_mutex_unlock(&simulation->print_mutex);
			break ;
		}
		// Add a short sleep to prevent tight looping and reduce CPU usage
		usleep(1000); // for example, sleep for 1ms
	}
	return (NULL);
}

// Create a thread for each routine and monitoring.

// pthread_t philosopher_thread, monitor_thread;

// pthread_create(&philosopher_thread, NULL, philosopher_routine, &data);
// pthread_create(&monitor_thread, NULL, monitor_routine, &data);

// pthread_join(philosopher_thread, NULL);
// pthread_join(monitor_thread, NULL);
