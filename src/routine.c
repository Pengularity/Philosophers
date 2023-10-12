/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:25:06 by pengu             #+#    #+#             */
/*   Updated: 2023/10/12 05:18:16 by wnguyen          ###   ########.fr       */
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

void	is_eating(t_data *data)
{
	if (data->philo->id == data->config->philo_nb)
	{
		pthread_mutex_lock(data->philo->right_fork);
		pthread_mutex_lock(data->philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(data->philo->left_fork);
		pthread_mutex_lock(data->philo->right_fork);
	}
	print_status(data, "\033[90mhas taken a fork\033[0m");
	print_status(data, "\033[91mis eating\033[0m");
	pthread_mutex_lock(&data->philo->last_time_ate_mutex);
	gettimeofday(&data->philo->last_time_ate, NULL);
	pthread_mutex_unlock(&data->philo->last_time_ate_mutex);
	ft_sleep(data->config->time_to_eat);
	pthread_mutex_lock(&data->philo->times_eaten_mutex);
	data->philo->times_eaten++;
	pthread_mutex_unlock(&data->philo->times_eaten_mutex);

	if (data->config->nb_must_eat > 0
		&& data->philo->times_eaten >= data->config->nb_must_eat)
	{
		pthread_mutex_lock(&data->simulation->ate_enough_mutex);
		data->philo->ate_enough = 1;
		data->simulation->nb_ate_enough++;
		printf("NB PHILO FINISHED : %d\n", data->simulation->nb_ate_enough);
		pthread_mutex_unlock(&data->simulation->ate_enough_mutex);
	}
	pthread_mutex_unlock(data->philo->left_fork);
	pthread_mutex_unlock(data->philo->right_fork);
}

void	is_sleeping_and_thinking(t_data *data)
{
	print_status(data, "\033[94mis sleeping\033[0m");
	ft_sleep(data->config->time_to_sleep);
	print_status(data, "\033[92mis thinking\033[0m");
}

void	*philosopher_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->philo->id % 2 == 0)
		usleep(data->config->time_to_eat / 10);

	while (get_status(data) == ONGOING)
	{
		printf("%d\n", data->philo->ate_enough);
		is_eating(data);
		if (data->philo->ate_enough == 1)
			{
				free(data);
				break ;
			}
		is_sleeping_and_thinking(data);
	}

	return (NULL);
}

