/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:16:27 by tas               #+#    #+#             */
/*   Updated: 2023/02/17 18:17:29 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simu(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->dead_lock);
	res = data->flag_simu;
	pthread_mutex_unlock(&data->dead_lock);
	return (res);
}

int	incr_simu(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->flag_simu += 1;
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

int	check_time_death(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->print_lock);
	if (((get_time() - data->start_time) - philo->last_meal) > \
		data->time_to_die)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (data->flag_simu >= 1)
			return (pthread_mutex_unlock(&data->dead_lock), 0);
		pthread_mutex_unlock(&data->dead_lock);
		incr_simu(data);
		printf("\033[1;33m%ld\033[0m %d \033[31m%s\033[0m \U0001f480\n", \
		get_time() - data->start_time, philo->id, DIED);
		pthread_mutex_unlock(&data->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->print_lock);
	return (0);
}

void	*check_death(void *d)
{
	int		i;
	t_data	*data;
	t_philo	**philo;

	data = d;
	philo = data->first_philo;
	while (!check_simu(data))
	{
		i = 0;
		while (i < data->nb_of_philo)
		{
			if (check_time_death(data, philo[i]) == 1)
				return (0);
			i++;
		}
	}
	return (0);
}

void	*check_meals(void *d)
{
	int		i;
	t_data	*data;
	t_philo	**philo;

	i = 0;
	data = d;
	philo = data->first_philo;
	while (check_simu(data) == 0)
	{
		if (data->nb_of_meal == -1)
			return (0);
		while (i < data->nb_of_philo && check_simu(data) == 0)
		{
			pthread_mutex_lock(&data->meal_lock);
			if ((philo[i]->meals_took < data->nb_of_meal))
				i = 0;
			i++;
			pthread_mutex_unlock(&data->meal_lock);
		}
		incr_simu(data);
		return (0);
	}
	return (0);
}
