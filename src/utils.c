/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnguyen <wnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:32:04 by pengu             #+#    #+#             */
/*   Updated: 2023/10/07 18:38:58 by wnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long int	timeval_to_millis(struct timeval *tv)
{
	return ((tv->tv_sec * 1000) + (tv->tv_usec / 1000));
}

long int	current_time(void)
{
	long int		time;
	struct timeval	current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;
	long int	elapsed_time;

	start_time = current_time();
	elapsed_time = 0;
	while (elapsed_time < time_in_ms)
	{
		if (time_in_ms - elapsed_time > 100)
			usleep(10 * 1000);
		else
			usleep((time_in_ms - elapsed_time) * 1000);
		elapsed_time = current_time() - start_time;
	}
}
