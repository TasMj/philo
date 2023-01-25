/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:30:56 by tas               #+#    #+#             */
/*   Updated: 2023/01/25 11:21:07 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data, char **argv, int argc)
{
    data->nb_of_philo = ft_atoi(argv[1]);
    if (data->nb_of_philo == 0)
        return(err_msg(3));
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->start_time = get_time();
    data->is_dead = 0;
    if (argc == 6)
        data->nb_of_meal = ft_atoi(argv[5]);
    else if (argc == 5)
        data->nb_of_meal = -1;
    return (0);
}

int init_philo(t_philo *philo,t_data *data)
{
    int i;

    philo = malloc(sizeof(t_philo) * data->nb_of_philo);
    if (!philo)
        return (err_msg(6));

    if (data->nb_of_philo == 1)
    {
        philo->id = 1;
        philo->data = data;
        philo->left_fork = philo->id;
        if (pthread_create(&philo[0].thread, NULL, &routine_one_philo, &philo[0]) != 0)
            return (err_msg(5));
        if (pthread_join(philo[0].thread, NULL) != 0)
            return (err_msg(5));
        return (0);
    }
    i = 0;
    // philo->begining = philo;
    while (i < data->nb_of_philo - 1)
    {
        philo->id = i + 1;
        philo->data = data;
        philo->meals_took = 0;
        philo->left_fork = philo->id;
        if (i == data->nb_of_philo - 1)
            philo->right_fork = 1;
        else
            philo->right_fork = philo->id + 1;
        data->philo = philo;
	// printf("%d --> left: %d, right: %d\n", philo->id, philo->left_fork, philo->right_fork);
        
        init_thread(philo, i);
        i++;
    }
    return (0);
}

int init_thread(t_philo *philo, int i)
{
    printf("***ENTER INIT THREAD***\n");
	printf("%d --> left: %d, right: %d\n", philo->id, philo->left_fork, philo->right_fork);
    printf("i: %d\n", i);
    if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
        return (err_msg(5));
    if (pthread_join(philo[i].thread, NULL) != 0)
        return (err_msg(5));
    // i++;
    return (0);
}

// int init_thread(t_data *data)
// {
    // int i;
    // t_philo *philo;
// 
    // i = 1;
    // philo = data->philo;
    // printf("***ENTER INIT THREAD***\n");
	// printf("%d --> left: %d, right: %d\n", philo->id, philo->left_fork, philo->right_fork);
    // 
    // while (i < data->nb_of_philo + 1)
    // {
   	// printf("%d --> left: %d, right: %d\n", philo->id, philo->left_fork, philo->right_fork);
        // if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
            // return (err_msg(5));
        // if (pthread_join(philo[i].thread, NULL) != 0)
            // return (err_msg(5));
        // i++;
    // }
    // return (0);
// }

int init_mutex(t_data *data)
{
    int i;

    i = 0;
    data->forks_lock = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
    if (!data)
        return (err_msg(6));
    while (i < data->nb_of_philo)
    {
        if (pthread_mutex_init(&data->forks_lock[i], NULL) != 0)
            return (err_msg(7));
        i++;
    }
    // if (pthread_mutex_init(&data->print_status_lock, NULL) != 0)
        // return (err_msg(7));
    // if (pthread_mutex_init(&data->death_lock, NULL) != 0)
        // return (err_msg(7));
    // if (pthread_mutex_init(&data->meals_lock, NULL) != 0)
        // return (err_msg(7));
    return (0);
}
