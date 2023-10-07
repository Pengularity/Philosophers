/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:37:52 by pengu             #+#    #+#             */
/*   Updated: 2023/10/07 23:02:06 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

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
	struct timeval	last_time_ate;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}						t_philosopher;

typedef struct s_simulation
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		status_mutex;
	pthread_mutex_t		times_eaten_mutex;
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
void		cleanup(pthread_t *philosophers, t_data *data);

/*libft*/

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *str, int fd);
int			ft_atoi(const char *str);
int			ft_strlen(char *str);

/*routine*/

void		*philosopher_routine(void *arg);
void		print_status(t_data *data, char *status);

/*monitoring*/

void		*monitoring(void *arg);
void		update_status(t_data *data, t_simulation_status new_status);

/*utils*/

int			ft_error(char *str);
long int	current_time(void);
void		ft_usleep(long int time_in_ms);

#endif
