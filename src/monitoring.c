/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:12:24 by wnguyen           #+#    #+#             */
/*   Updated: 2023/10/12 05:04:22 by wnguyen          ###   ########.fr       */
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

void	*monitoring(void *arg)
{
	t_data		*data;
	long int	time_since_last_meal;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->philo->last_time_ate_mutex);
		time_since_last_meal = current_time()
			- timeval_to_millis(&data->philo->last_time_ate);
		if (time_since_last_meal > data->config->time_to_die)
		{
			print_status(data, "\033[91mdied\033[0m");
			update_status(data, PHILOSOPHER_DIED);
			pthread_mutex_unlock(&data->philo->last_time_ate_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->philo->last_time_ate_mutex);
		pthread_mutex_lock(&data->simulation->ate_enough_mutex);
		if (data->simulation->nb_ate_enough == data->config->philo_nb)
		{
			pthread_mutex_unlock(&data->simulation->ate_enough_mutex);
			update_status(data, ALL_ATE_REQUIRED_TIMES);
			printf("ALL ATE REQUIRED TIMES\n");
			break ;
		}
		pthread_mutex_unlock(&data->simulation->ate_enough_mutex);
		usleep(1000);
	}

	return (NULL);
}

// Create a thread for each routine and monitoring.

// pthread_t philosopher_thread, monitor_thread;

// pthread_create(&philosopher_thread, NULL, philosopher_routine, &data);
// pthread_create(&monitor_thread, NULL, monitor_routine, &data);

// pthread_join(philosopher_thread, NULL);
// pthread_join(monitor_thread, NULL);
