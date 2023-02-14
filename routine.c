/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/02/14 14:19:07 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_one_philo(void *d)
{
	t_philo	*philo;

	philo = d;
	pthread_mutex_lock(&philo->data->forks_lock[0]);
	printf("\033[1;33m%ld\033[0m %d \033[35m%s\033[0m \U0001f374\n", get_time() - philo->data->start_time, 1, FORK);
	usleep(philo->data->time_to_die * 1000);
	printf("\033[1;33m%ld\033[0m %d \033[31m%s\033[0m \U0001f480\n", get_time() - philo->data->start_time, 1, DIED);
	pthread_mutex_unlock(&philo->data->forks_lock[0]);
	return (0);
}

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
		// usleep(data->time_to_die * 1000);
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

void	*routine(void *d)
{
	t_philo	*philo;

	philo = d;
	while (check_simu(philo->data) == 0)
	{
		if (philo->data->nb_of_philo == 3)
		{
			// printf("3\n");
			three_eat(philo, philo->data);
		}
		else if (philo->data->nb_of_philo % 2 != 0 && philo->data->nb_of_philo != 3)
			odd_eat(philo, philo->data);
		else
		{
			eat(philo, philo->data);
			sleep_and_think(philo, philo->data);
		}
	}
	return (0);
}

/*nb imp de philo*/

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
	if (philo->id != data->nb_of_philo && data->nb_of_philo % 2 != 0)
		usleep(data->time_to_eat);
	return (0);
}

/*eat for 3*/
int	three_eat(t_philo *philo, t_data *data)
{
	if ((philo->meals_took == 0) && philo->id == 2)
		usleep(data->time_to_eat * 1000);
	if ((philo->meals_took == 0) && philo->id == 3)
		usleep((data->time_to_eat * 1000) * 2);
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
	usleep((data->time_to_eat + data->time_to_sleep));
	return (0);
}


	    //if(philo->data->flag_simu != 1 && (philo->meals_took < philo->data->nb_of_meal 
	            // || philo->data->nb_of_meal == -1))
