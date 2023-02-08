/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:29:46 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/08 01:05:33 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	print_status(char s, t_philo *philo, t_data *data)
{
	time_t	timestamp;

	timestamp = get_time() - data->start_time;
	pthread_mutex_lock(data->print_lock);
	if (s == 'f')
		printf("\033[1;33m%ld\033[0m %d \033[35m%s\033[0m \U0001f374\n", timestamp, philo->id, FORK);
	if (s == 'e')
	{
		philo->last_meal = timestamp;
		printf("\033[1;33m%ld\033[0m %d \033[36m%s\033[m \U0001f355\n", timestamp, philo->id, EAT);
	}
	if (s == 's')
		printf("\033[1;33m%ld\033[0m %d \033[1;32m%s\033[0m \U0001f6CC\n", timestamp, philo->id, SLEEP);
	if (s == 't')
		printf("\033[1;33m%ld\033[0m %d \033[33m%s\033[0m \U0001f914\n", timestamp, philo->id, THINK);
	if (s == 'd')
	{
		printf("\033[1;33m%ld\033[0m %d \033[31m%s\033[0m \U0001f480\n", timestamp, philo->id, DIED);
		pthread_mutex_unlock(data->print_lock);
		return (1);
	}
	pthread_mutex_unlock(data->print_lock);
	return (0);
}
