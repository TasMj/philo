/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:29:46 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/17 18:23:04 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	print_status(char s, t_philo *philo, t_data *data)
{
	time_t	timestamp;

	timestamp = get_time() - data->start_time;
	pthread_mutex_lock(&data->print_lock);
	if (check_simu(data))
		return (pthread_mutex_unlock(&data->print_lock), 0);
	if (s == 'f')
		printf("\033[1;33m%ld\033[0m %d \033[35m%s\033[0m \U0001f374\n", \
		timestamp, philo->id, FORK);
	else if (s == 'e')
	{
		philo->last_meal = timestamp;
		printf("\033[1;33m%ld\033[0m %d \033[36m%s\033[m \U0001f35D\n", \
		timestamp, philo->id, EAT);
	}
	else if (s == 's')
		printf("\033[1;33m%ld\033[0m %d \033[1;32m%s\033[0m \U0001f6CC\n", \
		timestamp, philo->id, SLEEP);
	else if (s == 't')
		printf("\033[1;33m%ld\033[0m %d \033[33m%s\033[0m \U0001f914\n", \
		timestamp, philo->id, THINK);
	pthread_mutex_unlock(&data->print_lock);
	return (0);
}

int	u_sleep(t_data *data, time_t time)
{
	time_t	i;

	i = get_time();
	while (get_time() - i < time)
	{
		if (check_simu(data) == 1)
			return (1);
		usleep(50);
	}
	return (0);
}
