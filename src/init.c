/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:46:20 by pengu             #+#    #+#             */
/*   Updated: 2023/10/07 23:16:58 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_positive(char *str)
{
	int	i;

	if (!str || str[0] == '0')
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (i > 0 && ft_atoi(str) > 0);
}

t_data	*init_data_structure(int philo_nb)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->simulation = malloc(sizeof(t_simulation));
	data->philo = malloc(sizeof(t_philosopher) * philo_nb);
	data->simulation->forks = malloc(sizeof(pthread_mutex_t) * philo_nb);
	if (!data->simulation || !data->philo || !data->simulation->forks)
		return (cleanup(data, NULL), NULL);
	pthread_mutex_init(&data->simulation->print_mutex, NULL);
	i = 0;
	while (i < data->config->philo_nb)
	{
		pthread_mutex_init(&data->simulation->forks[i], NULL);
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = &data->simulation->forks[i];
		data->philo[i].right_fork = &data->simulation->forks[(i + 1)
			% data->config->philo_nb];
		gettimeofday(&data->philo[i].last_time_ate, NULL);
		data->philo[i].times_eaten = 0;
		i++;
	}
	return (data);
}

int	parse_args(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (ft_error(" Invalid numbers of arguments"));
	while (i < ac)
	{
		if (!is_positive(av[i]))
			return (ft_error("All arguments must be positive"));
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

void	cleanup(pthread_t *philosophers, t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return ;
	if (data->simulation)
	{
		if (data->simulation->forks)
		{
			while (i < data->config->philo_nb)
			{
				pthread_mutex_destroy(&data->simulation->forks[i]);
				if (philosophers)
					pthread_join(philosophers[i], NULL);
				i++;
			}
			free(data->simulation->forks);
		}
		pthread_mutex_destroy(&data->simulation->print_mutex);
		pthread_mutex_destroy(&data->simulation->status_mutex);
		free(data->simulation);
	}
	free(data->philo);
	free(data);
	free(philosophers);
}
