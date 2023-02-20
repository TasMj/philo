/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:24:33 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/15 16:54:48 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	init_only_one_philo(t_philo **philo, t_data *data)
{
	philo[0] = malloc(sizeof(t_philo) * 1);
	data->first_philo = &philo[0];
	if (!philo[0])
		return (err_msg(6));
	(*philo)[0].id = 1;
	(*philo)[0].data = data;
	(*philo)[0].left_fork = (*philo)[0].id;
	if (pthread_create(&(*philo)[0].thread, NULL, &routine_one_philo, \
		&(*philo)[0]) != 0)
		return (err_msg(5));
	if (pthread_join((*philo)[0].thread, NULL) != 0)
		return (err_msg(5));
	return (0);
}

int	join_thread(t_data *data)
{
	if (pthread_join(data->watch_death, NULL) != 0)
		return (err_msg(5));
	if (pthread_join(data->watch_meals, NULL) != 0)
		return (err_msg(5));
	return (0);
}
