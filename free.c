/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:33:05 by tas               #+#    #+#             */
/*   Updated: 2023/02/09 21:07:23 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*free philo*/
int	free_philos(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	philo = data->first_philo;
	while (i < data->nb_of_philo)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
	return (0);
}

/*free data*/
int	free_data(t_data *data)
{
	free(data->forks_lock);
	free_philos(data->first_philo, data);
	return (0);
}

/*free mutex*/
void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (&data->forks_lock[i])
			pthread_mutex_destroy(&data->forks_lock[i]);
		i++;
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->print_lock);
}

/*free all at the end*/
int	free_all(t_data *data, t_philo **philo)
{
	destroy_mutex(data);
	free_data(data);
	free(philo);
	return (0);
}
