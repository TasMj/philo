/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/02/15 20:59:26 by tmejri           ###   ########.fr       */
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

int	eat(t_philo *philo, t_data *data)
{
	if ((philo->meals_took == 0) && (philo->id % 2 == 0))
		u_sleep(data, data->time_to_eat / 3);
	fork_process(philo, data);
	u_sleep(data, data->time_to_eat);
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
	if ((philo->meals_took == 0) && (philo->id == data->nb_of_philo))
		usleep((data->time_to_eat) * 2);
	if ((philo->meals_took == 0) && (philo->id % 2 == 0))
		usleep(data->time_to_eat);
	fork_process(philo, data);
	u_sleep(data, data->time_to_eat);
	pthread_mutex_unlock(&data->forks_lock[philo->right_fork]);
	pthread_mutex_unlock(&data->forks_lock[philo->left_fork]);
	pthread_mutex_lock(&data->meal_lock);
	philo->meals_took++;
	pthread_mutex_unlock(&data->meal_lock);
	sleep_and_think(philo, data);
	usleep((data->time_to_eat + data->time_to_sleep));
	return (0);
}

void	*routine(void *d)
{
	t_philo	*philo;

	philo = d;
	while (check_simu(philo->data) == 0)
	{
		if (philo->data->nb_of_philo % 2 != 0)
			odd_eat(philo, philo->data);
		else
		{
			eat(philo, philo->data);
			sleep_and_think(philo, philo->data);
		}
	}
	return (0);
}
