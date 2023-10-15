/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:37:52 by pengu             #+#    #+#             */
/*   Updated: 2023/10/15 21:24:49 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef enum e_simulation_status
{
	ONGOING,
	PHILOSOPHER_DIED,
	ALL_ATE_REQUIRED_TIMES
}				t_simulation_status;

typedef struct s_philosopher
{
	int				id;
	int				times_eaten;
	pthread_mutex_t	times_eaten_mutex;
	pthread_mutex_t	last_time_ate_mutex;
	int				ate_enough;
	pthread_t		thread_id;
	pthread_t		thread_death_id;
	struct timeval	last_time_ate;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}						t_philosopher;

typedef struct s_simulation
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		status_mutex;
	pthread_mutex_t		ate_enough_mutex;
	pthread_mutex_t		dead_mutex;
	long int			start_time;
	int					nb_ate_enough;
}					t_simulation;

typedef struct s_config
{
	int	philo_nb;
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

/*init and parse*/

int			parse_args(int ac, char **av, t_data *data);
t_data		*init_data_structure(int philo_nb);
void		cleanup(t_data *data, pthread_t *philosophers);

/*libft*/

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *str, int fd);
int			ft_atoi(const char *str);
int			ft_strlen(char *str);

/*routine*/

void		*philosopher_routine(void *arg);
void		print_status(t_data *data, char *status);

/*monitoring*/

t_simulation_status	get_status(t_data *data);
void		*monitoring(void *arg);
void		update_status(t_data *data, t_simulation_status new_status);

/*utils*/

int			ft_error(char *str);
long int	current_time(void);
void		ft_sleep(long int time_in_ms);

/*thread*/

pthread_t	*create_philosophers(t_data *data);
void		wait_for_philosophers(pthread_t *philosophers, int philo_nb);

/*free*/

void		cleanup(t_data *data, pthread_t *philosophers);

#endif
