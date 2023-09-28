/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:25:06 by pengu             #+#    #+#             */
/*   Updated: 2023/09/29 00:19:20 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status(t_data *data, char *status)
{
	t_simulation	*simulation;

	simulation = data->philo->simulation;
	pthread_mutex_lock(&data->simulation->print_mutex);
	printf("%ld %d %s\n", current_time(), data->philo->id, status);
	pthread_mutex_unlock(&data->simulation->print_mutex);
}

void	think(t_data *data)
{
	print_status(data, "is thinking");
	// Implementation delay thinking.
}

void	eat(t_data *data)
{
	t_simulation	*simulation;

	simulation = data->philo->simulation;
	if (data->philo->id == simulation->philo_nb)
	{
		pthread_mutex_lock(data->philo->right_fork);
		pthread_mutex_lock(data->philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(data->philo->left_fork);
		pthread_mutex_lock(data->philo->right_fork);
	}
	print_status(data, "has taken a fork");
	print_status(data, "is eating");
	gettimeofday(&data->philo->last_time_ate, NULL);
	ft_sleep(simulation->config->time_to_eat);
	data->philo->times_eaten++;
	if (simulation->config->nb_must_eat > 0
		&& data->philo->times_eaten >= simulation->config->nb_must_eat)
		simulation->status = ALL_ATE_REQUIRED_TIMES;
	pthread_mutex_unlock(data->philo->left_fork);
	pthread_mutex_unlock(data->philo->right_fork);
}

void	sleep(t_data *data)
{
	t_simulation	*simulation;

	simulation = data->philo->simulation;
	print_status(data, "is sleeping");
	ft_sleep(simulation->config->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_data			*data;
	t_simulation	*simulation;
	long int		time_last_meal;

	data = (t_data *)arg;
	simulation = data->philo->simulation;
	while (simulation->status == ONGOING)
	{
		think(data);
		eat(data);
		sleep(data);

	}
	return (NULL);
}
