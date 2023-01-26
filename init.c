/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:30:56 by tas               #+#    #+#             */
/*   Updated: 2023/01/26 19:37:09 by tas              ###   ########.fr       */
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

int init_only_one_philo(t_philo **philo, t_data *data)
{
    philo[0] = malloc(sizeof(t_philo) * 1);
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

int init_philo(t_philo **philo,t_data *data)
{
    int i;

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
        // (*philo)[i].data = data;
        philo[i]->id = i + 1;
        philo[i]->meals_took = 0;
        philo[i]->left_fork = philo[i]->id;
        philo[i]->right_fork = philo[i]->id + 1;
        if (i == data->nb_of_philo - 1)
        {
            philo[i]->right_fork = 1;
        }
	    printf("%d --> left: %d, right: %d\n", philo[i]->id, philo[i]->left_fork, philo[i]->right_fork);
        i++;
    }
    printf("\n\n\n");
    return (0);
}

// int init_thread_2(t_philo *philo, int i)
// {
    // printf("***ENTER INIT THREAD***\n");
	// printf("%d --> left: %d, right: %d", philo->id, philo->left_fork, philo->right_fork);
    // printf("i: %d\n", i);
    // if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
        // return (err_msg(5));
    // if (pthread_join(philo[i].thread, NULL) != 0)
        // return (err_msg(5));
    // return (0);
// }

// int init_thread(t_data *data)
// {
//     printf("***ENTER INIT THREAD***\n");
    
//     t_philo *philo = data->philo;

//     printf("philo id: %d\n", philo->id);
//     // 
//     int i;
//     t_philo *philo;

//     i = 1;
//     philo = data->first_philo;
    
//     while (i < philo->data->nb_of_philo)
//     {
//    	printf("%d --> left: %d, right: %d -->", philo->id, philo->left_fork, philo->right_fork);
//         if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
//             return (err_msg(5));
//         if (pthread_join(philo[i].thread, NULL) != 0)
//             return (err_msg(5));
//         i++;
//     }
//     return (0);
// }


int init_thread(t_data *data)
{
    printf("***ENTER INIT THREAD***\n\n");

    t_philo **philo;
    int i;

    i = 0;
    philo = data->first_philo;
    
    while (i < data->nb_of_philo)
    {
   	printf("%d --> left: %d, right: %d -->", philo[i]->id, philo[i]->left_fork, philo[i]->right_fork);
        if (pthread_create(&(*philo)[i].thread, NULL, &routine, &(*philo)[i]) != 0)
            return (err_msg(5));
        if (pthread_join((*philo)[i].thread, NULL) != 0)
            return (err_msg(5));

        i++;
    }
    // i = 0;
    // while (i < data->nb_of_philo)
    // {
        // if (pthread_join((*philo)[i].thread, NULL) != 0)
            // return (err_msg(5));
        // i++;
    // } 
    return (0);
}

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
