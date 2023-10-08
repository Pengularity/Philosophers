/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:25:06 by pengu             #+#    #+#             */
/*   Updated: 2023/10/08 19:45:33 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status(t_data *data, char *status)
{
	pthread_mutex_lock(&data->simulation->print_mutex);
	printf("%ld %d %s\n", current_time() - data->simulation->start_time,
		data->philo->id, status);
	pthread_mutex_unlock(&data->simulation->print_mutex);
}

void	is_thinking(t_data *data)
{
	print_status(data, "\033[92mis thinking\033[0m");
}

void	is_eating(t_data *data)
{
	if (data->philo->id == data->config->philo_nb)
		(pthread_mutex_lock(data->philo->right_fork),
			pthread_mutex_lock(data->philo->left_fork));
	else
		(pthread_mutex_lock(data->philo->left_fork),
			pthread_mutex_lock(data->philo->right_fork));
	print_status(data, "\033[90mhas taken a fork\033[0m");
	print_status(data, "\033[91mis eating\033[0m");
	gettimeofday(&data->philo->last_time_ate, NULL);
	ft_sleep(data->config->time_to_eat);
	pthread_mutex_lock(&data->simulation->times_eaten_mutex);
	data->philo->times_eaten++;
	pthread_mutex_unlock(&data->simulation->times_eaten_mutex);
	if (data->config->nb_must_eat > 0
		&& data->philo->times_eaten >= data->config->nb_must_eat)
		update_status(data, ALL_ATE_REQUIRED_TIMES);
	pthread_mutex_unlock(data->philo->left_fork);
	pthread_mutex_unlock(data->philo->right_fork);
}

void	is_sleeping(t_data *data)
{
	print_status(data, "\033[94mis sleeping\033[0m");
	ft_sleep(data->config->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_data			*data;
	// long int		time_last_meal;

	data = (t_data *)arg;
	while (data->status == ONGOING)
	{
		is_thinking(data);
		is_eating(data);
		is_sleeping(data);

	}
	return (NULL);
}
