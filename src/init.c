/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:46:20 by pengu             #+#    #+#             */
/*   Updated: 2023/10/12 05:03:40 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_positive(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (i > 0);
}

int	parse_args(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_positive(av[i]))
			return (ft_error("Invalid arguments"));
		i++;
	}
	data->config->philo_nb = ft_atoi(av[1]);
	data->config->time_to_die = ft_atoi(av[2]);
	data->config->time_to_eat = ft_atoi(av[3]);
	data->config->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->config->nb_must_eat = ft_atoi(av[5]);
	else
		data->config->nb_must_eat = -1;
	return (1);
}

t_data	*init_malloc(int philo_nb)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->config = malloc(sizeof(t_config));
	data->simulation = malloc(sizeof(t_simulation));
	data->philo = malloc(sizeof(t_philosopher) * philo_nb);
	data->simulation->forks = malloc(sizeof(pthread_mutex_t) * philo_nb);
	if (!data->simulation || !data->philo || !data->simulation->forks)
	{
		cleanup(data, NULL);
		return (NULL);
	}
	return (data);
}

void	init_philosopher(t_data *data, int i)
{
	pthread_mutex_init(&data->philo[i].times_eaten_mutex, NULL);
	pthread_mutex_init(&data->simulation->forks[i], NULL);
	data->philo[i].id = i + 1;
	data->philo[i].left_fork = &data->simulation->forks[i];
	data->philo[i].right_fork = &data->simulation->forks[(i + 1)
		% data->config->philo_nb];
	gettimeofday(&data->philo[i].last_time_ate, NULL);
	data->philo[i].times_eaten = 0;
	data->philo[i].ate_enough = 0;
}

t_data	*init_data_structure(int philo_nb)
{
	t_data	*data;
	int		i;

	data = init_malloc(philo_nb);
	if (!data)
		return (NULL);
	data->config->philo_nb = philo_nb;
	pthread_mutex_init(&data->simulation->print_mutex, NULL);
	pthread_mutex_init(&data->philo->times_eaten_mutex, NULL);
	pthread_mutex_init(&data->philo->last_time_ate_mutex, NULL);
	pthread_mutex_init(&data->simulation->ate_enough_mutex, NULL);
	pthread_mutex_init(&data->simulation->dead_mutex, NULL);
	data->simulation->start_time = current_time();
	data->status = ONGOING;
	i = 0;
	while (i < philo_nb)
	{
		init_philosopher(data, i);
		i++;
	}
	return (data);
}
