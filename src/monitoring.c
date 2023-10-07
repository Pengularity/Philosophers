/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:12:24 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/07 22:51:50 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	timeval_to_millis(struct timeval *tv)
{
	return ((tv->tv_sec * 1000) + (tv->tv_usec / 1000));
}

void	update_status(t_data *data, t_simulation_status new_status)
{
	pthread_mutex_lock(&data->simulation->status_mutex);
	data->status = new_status;
	pthread_mutex_unlock(&data->simulation->status_mutex);
}

t_simulation_status	get_status(t_data *data)
{
	t_simulation_status	current_status;

	pthread_mutex_lock(&data->simulation->status_mutex);
	current_status = data->status;
	pthread_mutex_unlock(&data->simulation->status_mutex);

	return (current_status);
}

void	check_all_ate_enough(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->config->philo_nb)
	{
		if (data->philo[i].times_eaten < data->config->nb_must_eat)
			return ;
		i++;
	}
	update_status(data, ALL_ATE_REQUIRED_TIMES);
}


void	*monitoring(void *arg)
{
	t_data			*data;
	t_simulation	*simulation;
	long int		time_since_last_meal;

	data = (t_data *)arg;
	simulation = data->simulation;
	while (data->status == ONGOING)
	{
		time_since_last_meal = current_time()
			- (timeval_to_millis(&data->philo->last_time_ate));
		if (time_since_last_meal > data->config->time_to_die)
		{
			print_status(data, "died");
			update_status(data, PHILOSOPHER_DIED);
			break ;
		}
		check_all_ate_enough(data);
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
