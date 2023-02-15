/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/02/15 16:02:32 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo, t_data *data)
{
	if ((philo->meals_took == 0) && (philo->id % 2 == 0))
		usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&data->forks_lock[philo->left_fork]);
	if (check_simu(data) == 0)
		print_status('f', philo, data);
	pthread_mutex_lock(&data->forks_lock[philo->right_fork]);
	if (check_simu(data) == 0)
	{
		print_status('f', philo, data);
		print_status('e', philo, data);
	}
	if (data->time_to_eat > data->time_to_die)
		u_sleep(data, data->time_to_die * 1000);
	else
		usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks_lock[philo->right_fork]);
	pthread_mutex_unlock(&data->forks_lock[philo->left_fork]);
	pthread_mutex_lock(&data->meal_lock);
	philo->meals_took++;
	pthread_mutex_unlock(&data->meal_lock);
	return (0);
}

int	sleep_and_think(t_philo *philo, t_data *data)
{
	if (check_simu(data) == 0)
		print_status('s', philo, data);
	if (data->time_to_sleep > data->time_to_die)
		usleep(data->time_to_die * 1000);
	else
		usleep(data->time_to_sleep * 1000);
	if (check_simu(data) == 0)
		print_status('t', philo, philo->data);
	return (0);
}

/*odd number of philo*/
int	odd_eat(t_philo *philo, t_data *data)
{
	if ((philo->meals_took == 0) && (philo->id == data->nb_of_philo && data->nb_of_philo > 3))
		usleep((data->time_to_eat * 1000) * 2);
	if ((philo->meals_took == 0) && (philo->id % 2 == 0))
		usleep(data->time_to_eat * 1000);
	pthread_mutex_lock(&data->forks_lock[philo->left_fork]);
	if (check_simu(data) == 0)
		print_status('f', philo, data);
	pthread_mutex_lock(&data->forks_lock[philo->right_fork]);
	if (check_simu(data) == 0)
	{
		print_status('f', philo, data);
		print_status('e', philo, data);
	}
	if (data->time_to_eat > data->time_to_die)
		u_sleep(data, data->time_to_die * 1000);
	else
		usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks_lock[philo->right_fork]);
	pthread_mutex_unlock(&data->forks_lock[philo->left_fork]);
	pthread_mutex_lock(&data->meal_lock);
	philo->meals_took++;
	pthread_mutex_unlock(&data->meal_lock);
	sleep_and_think(philo, data);
	if (data->time_to_sleep < data->time_to_eat)
		usleep((data->time_to_eat + data->time_to_sleep) * 1000);
	else
		usleep((data->time_to_eat + data->time_to_sleep));
	return (0);
}

/*eat for 3 philos because they have to eat one by one*/
int	three_eat(t_philo *philo, t_data *data)
{
	// printf("%ld: last meal of [%d]\n", philo->last_meal, philo->id);
	if ((philo->meals_took == 0) && philo->id == 2)
		usleep(data->time_to_eat * 1000);
	if ((philo->meals_took == 0) && philo->id == 3)
		usleep((data->time_to_eat * 1000) * 2);
	if ((philo->meals_took != 0))
		usleep((data->time_to_eat + data->time_to_sleep) * 1000);
	pthread_mutex_lock(&data->forks_lock[philo->left_fork]);
	if (check_simu(data) == 0)
		print_status('f', philo, data);
	pthread_mutex_lock(&data->forks_lock[philo->right_fork]);
	if (check_simu(data) == 0)
	{
		print_status('f', philo, data);
		print_status('e', philo, data);
	}
	if (data->time_to_eat > data->time_to_die)
		u_sleep(data, data->time_to_die * 1000);
	else
		usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks_lock[philo->right_fork]);
	pthread_mutex_unlock(&data->forks_lock[philo->left_fork]);
	pthread_mutex_lock(&data->meal_lock);
	philo->meals_took++;
	pthread_mutex_unlock(&data->meal_lock);
	sleep_and_think(philo, data);
	return (0);
}

void	*routine(void *d)
{
	t_philo	*philo;

	philo = d;
	while (check_simu(philo->data) == 0)
	{
		if (philo->data->nb_of_philo == 3)
			three_eat(philo, philo->data);
		else if (philo->data->nb_of_philo % 2 != 0 && philo->data->nb_of_philo > 3)
			odd_eat(philo, philo->data);
		else
		{
			eat(philo, philo->data);
			sleep_and_think(philo, philo->data);
		}
	}
	return (0);
}
