/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:30:56 by tas               #+#    #+#             */
/*   Updated: 2023/02/11 12:36:12 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **argv, int argc)
{
	data->nb_of_philo = ft_atoi(argv[1]);
	if (data->nb_of_philo == 0)
		return (err_msg(3));
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = get_time();
	data->flag_simu = 0;
	if (argc == 6)
	{
		data->nb_of_meal = ft_atoi(argv[5]);
		if (data->nb_of_meal == 0)
			return (err_msg(8));
	}
	else if (argc == 5)
		data->nb_of_meal = -1;
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
	if (pthread_create(&(*philo)[0].thread, NULL, &routine_one_philo, &(*philo)[0]) != 0)
		return (err_msg(5));
	if (pthread_join((*philo)[0].thread, NULL) != 0)
		return (err_msg(5));
	return (0);
}

int	init_philo(t_philo **philo, t_data *data)
{
	int	i;

	philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!philo)
		return (err_msg(6));
	if (data->nb_of_philo == 1)
	{
		init_only_one_philo(philo, data);
		return (0);
	}
	i = 0;
	data->first_philo = philo;
	while (i < data->nb_of_philo)
	{
		philo[i] = malloc(sizeof(t_philo) * 1);
		if (!philo[i])
			return (err_msg(6));
		philo[i]->data = data;
		philo[i]->id = i + 1;
		philo[i]->meals_took = 0;
		philo[i]->last_meal = 0;
		philo[i]->left_fork = philo[i]->id;
		philo[i]->right_fork = philo[i]->id + 1;
		if (i == data->nb_of_philo - 1)
		{
			philo[i]->left_fork = 1;
			philo[i]->right_fork = philo[i]->id;
		}
		i++;
	}
	return (0);
}

int	init_thread(t_data *data)
{
	int		i;
	t_philo	**philo;

	i = 0;
	philo = data->first_philo;
	while (i < data->nb_of_philo)
	{
		if (pthread_create(&(philo[i]->thread), NULL, &routine, philo[i]) != 0)
			return (err_msg(5));
		i++;
	}
	if (pthread_create(&data->watch_death, NULL, &check_death, data) != 0)
		return (err_msg(5));
	if (pthread_create(&data->watch_meals, NULL, &check_meals, data) != 0)
		return (err_msg(5));
	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_join(philo[i]->thread, NULL) != 0)
			return (err_msg(5));
		i++;
	}
	if (pthread_join(data->watch_death, NULL) != 0)
		return (err_msg(5));
	if (pthread_join(data->watch_meals, NULL) != 0)
		return (err_msg(5));
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks_lock = malloc(sizeof(pthread_mutex_t) * (data->nb_of_philo + 1));
	if (!data->forks_lock)
		return (err_msg(6));
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->forks_lock[i], NULL) != 0)
			return (err_msg(7));
		i++;
	}
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (err_msg(7));
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (err_msg(7));
	return (0);
}
