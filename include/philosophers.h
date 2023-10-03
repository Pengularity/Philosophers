/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:37:52 by pengu             #+#    #+#             */
/*   Updated: 2023/10/03 15:33:48 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>

typedef enum e_simulation_status
{
	ONGOING,
	PHILOSOPHER_DIED,
	ALL_ATE_REQUIRED_TIMES
}				t_simulation_status;

typedef struct s_philosopher
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	last_time_ate;
	int				times_eaten;
}						t_philosopher;

typedef struct s_simulation
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		status_mutex;
	int					philo_nb;
}					t_simulation;

typedef struct s_config
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_must_eat;
}				t_config;

typedef struct s_data
{
	t_philosopher		*philo;
	t_simulation		*simulation;
	t_config			*config;
	t_simulation_status	status;
}				t_data;

void		*philosopher_routine(void *arg);
long int	current_time(void);

#endif
