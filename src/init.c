/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:46:20 by pengu             #+#    #+#             */
/*   Updated: 2023/09/28 18:39:29 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_philo_and_forks(t_philosopher *philo,
	pthread_mutex_t *forks, int philo_nb)
{
	int	i;

	i = 0;
	while (i < philo_nb)
	{
		pthread_mutex_init(&forks[i], NULL);
		philo[i].id = i + 1;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % philo_nb];
		gettimeofday(&philo[i].last_time_ate, NULL);
		philo[i].times_eaten = 0;
		i++;
	}
}
