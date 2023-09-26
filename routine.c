/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pengu <pengu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:25:06 by pengu             #+#    #+#             */
/*   Updated: 2023/09/26 23:14:25 by pengu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


void    print_status(t_philosopher *philo, char *status)
{
    printf("%ld %d %s\n", current_time, philo->id, status);
}

void think(t_philosopher *philo)
{
    print_status(philo, "is thinking");
    // Implementation delay thinking.
}

void eat(t_philosopher *philo)
{
    t_simulation    *simulation = philo->simulation;

    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, "has taken a fork");
    print_status(philo, "is eating");
    gettimeofday(&philo->last_time_ate, NULL);
    ft_sleep(simulation->config->time_to_eat);
    philo->times_eaten++;
    if (simulation->config->nb_must_eat > 0 &&
        philo->times_eaten >= simulation->config->nb_must_eat)
            simulation->status = ALL_ATE_REQUIRED_TIMES;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);

}

void sleep(t_philosopher *philo)
{
    t_simulation *simulation = philo->simulation;
    
    print_status(philo, "is sleeping");
    ft_sleep(simulation->config->time_to_sleep);
}

void *philosopher_routine(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_simulation    *simulation = philo->simulation;

    while (simulation->status == ONGOING)
    {
        think(philo);
        eat(philo);
        sleep(philo);
    }
    return (NULL);
}
