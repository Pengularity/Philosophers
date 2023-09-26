/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pengu <pengu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:37:52 by pengu             #+#    #+#             */
/*   Updated: 2023/09/26 22:51:51 by pengu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <sys/time.h>

typedef enum    e_simulation_status
{
    ONGOING,
    PHILOSOPHER_DIED,
    ALL_ATE_REQUIRED_TIMES
}               t_simulation_status;

typedef struct s_config
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_must_eat;
}              t_config;

typedef struct s_simulation
{
    pthread_mutex_t     *forks;
    int                 philo_nb;
    t_config            *config;
    t_simulation_status status;
    t_philosopher       *philosophers;
}               t_simulation;

typedef struct s_philosopher
{
    int             id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct timeval  last_time_ate;
    int             times_eaten;
    t_simulation    *simulation;
}               t_philosopher;

void    *philosopher_routine(void *arg);
long int current_time(void);

#endif
