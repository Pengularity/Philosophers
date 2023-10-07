/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:25:06 by pengu             #+#    #+#             */
/*   Updated: 2023/10/07 23:06:14 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status(t_data *data, char *status)
{
	pthread_mutex_lock(&data->simulation->print_mutex);
	printf("%ld %d %s\n", current_time(), data->philo->id, status);
	pthread_mutex_unlock(&data->simulation->print_mutex);
}

void	think(t_data *data)
{
	print_status(data, "is thinking");
}

void	eat(t_data *data)
{
	if (data->philo->id == data->config->philo_nb)
		(pthread_mutex_lock(data->philo->right_fork),
			pthread_mutex_lock(data->philo->left_fork));
	else
		(pthread_mutex_lock(data->philo->left_fork),
			pthread_mutex_lock(data->philo->right_fork));
	print_status(data, "has taken a fork");
	print_status(data, "is eating");
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

void	sleep(t_data *data)
{
	print_status(data, "is sleeping");
	ft_sleep(data->config->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_data			*data;
	long int		time_last_meal;

	data = (t_data *)arg;
	while (data->status == ONGOING)
	{
		think(data);
		eat(data);
		sleep(data);

	}
	return (NULL);
}
