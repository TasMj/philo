/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/02/17 18:22:12 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_process(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks_lock[philo->left_fork]);
	if (check_simu(data) == 0)
		print_status('f', philo, data);
	pthread_mutex_lock(&data->forks_lock[philo->right_fork]);
	if (check_simu(data) == 0)
	{
		print_status('f', philo, data);
		print_status('e', philo, data);
	}
}

int	sleep_and_think(t_philo *philo, t_data *data)
{
	if (check_simu(data) == 0)
		print_status('s', philo, data);
	u_sleep(data, data->time_to_sleep);
	if (check_simu(data) == 0)
		print_status('t', philo, philo->data);
	return (0);
}

int	even(t_philo *philo, t_data *data)
{
	if ((philo->id % 2 == 0) && (philo->meals_took == 0))
		u_sleep(data, data->time_to_eat / 3);
	fork_process(philo, data);
	u_sleep(data, data->time_to_eat);
	pthread_mutex_unlock(&data->forks_lock[philo->right_fork]);
	pthread_mutex_unlock(&data->forks_lock[philo->left_fork]);
	pthread_mutex_lock(&data->meal_lock);
	philo->meals_took++;
	pthread_mutex_unlock(&data->meal_lock);
	sleep_and_think(philo, data);
	if (data->time_to_sleep == 0)
		u_sleep(data, data->time_to_eat / 3);
	return (0);
}

int	odd(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0 && (philo->meals_took == 0))
		u_sleep(data, data->time_to_eat / 3);
	if (philo->id == data->nb_of_philo && (philo->meals_took == 0))
		u_sleep(data, data->time_to_eat / 2);
	fork_process(philo, data);
	u_sleep(data, data->time_to_eat);
	pthread_mutex_unlock(&data->forks_lock[philo->right_fork]);
	pthread_mutex_unlock(&data->forks_lock[philo->left_fork]);
	pthread_mutex_lock(&data->meal_lock);
	philo->meals_took++;
	pthread_mutex_unlock(&data->meal_lock);
	sleep_and_think(philo, data);
	if (data->time_to_sleep == 0)
		u_sleep(data, data->time_to_eat / 3);
	u_sleep(data, (data->time_to_eat + data->time_to_sleep) / 3);
	return (0);
}

void	*routine(void *d)
{
	t_philo	*philo;

	philo = d;
	while (check_simu(philo->data) == 0)
	{
		if (philo->data->nb_of_philo % 2 != 0)
			odd(philo, philo->data);
		else
			even(philo, philo->data);
	}
	return (0);
}
