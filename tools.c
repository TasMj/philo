/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:29:46 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/14 17:43:47 by tas              ###   ########.fr       */
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
	pthread_mutex_lock(&data->print_lock);
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
		pthread_mutex_unlock(&data->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->print_lock);
	return (0);
}

int	u_sleep(t_data *data, time_t time)
{
	time_t	i;

	i = 0;
	while (i <= time)
	{
		if (check_simu(data) == 1)
			return (0);
		usleep(time / 50);
		i += (time / 50);
	}
	return (0);
}

void	*routine_one_philo(void *d)
{
	t_philo	*philo;

	philo = d;
	pthread_mutex_lock(&philo->data->forks_lock[0]);
	printf("\033[1;33m%ld\033[0m %d \033[35m%s\033[0m \U0001f374\n", \
	get_time() - philo->data->start_time, 1, FORK);
	usleep(philo->data->time_to_die * 1000);
	printf("\033[1;33m%ld\033[0m %d \033[31m%s\033[0m \U0001f480\n", \
	get_time() - philo->data->start_time, 1, DIED);
	pthread_mutex_unlock(&philo->data->forks_lock[0]);
	return (0);
}
