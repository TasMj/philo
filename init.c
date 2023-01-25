/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:30:56 by tas               #+#    #+#             */
/*   Updated: 2023/01/25 14:36:34 by tas              ###   ########.fr       */
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

int init_only_one_philo(t_philo **all_philo, t_data *data)
{
    all_philo[0] = malloc(sizeof(t_philo) * 1);
    if (!all_philo[0])
        return (err_msg(6));
    (*all_philo)[0].id = 1;
    (*all_philo)[0].data = data;
    (*all_philo)[0].left_fork = (*all_philo)[0].id;
    if (pthread_create(&(*all_philo)[0].thread, NULL, &routine_one_philo, &(*all_philo)[0]) != 0)
        return (err_msg(5));
    if (pthread_join((*all_philo)[0].thread, NULL) != 0)
        return (err_msg(5));
    return (0);
}

int init_philo(t_philo *philo,t_data *data)
{
    int i;
    (void)philo;
    t_philo **all_philo;

    all_philo = malloc(sizeof(t_philo) * data->nb_of_philo);
    if (!all_philo)
        return (err_msg(6));

    if (data->nb_of_philo == 1)
    {
        init_only_one_philo(all_philo, data);
        return (0);
    }
    i = 0;
    // data->philo = philo;
    while (i < data->nb_of_philo)
    {
        all_philo[i] = malloc(sizeof(t_philo) * 1);
        if (!all_philo[i])
            return (err_msg(6));
        (*all_philo)[i].data = data;
        (*all_philo)[i].id = i + 1;
        (*all_philo)[i].meals_took = 0;
        (*all_philo)[i].left_fork = (*all_philo)[i].id;
        if (i == data->nb_of_philo - 1)
            (*all_philo)[i].right_fork = 1;
        else
        {
            (*all_philo)[i].right_fork = (*all_philo)[i].id + 1;
        }
	    printf("%d --> left: %d, right: %d\n", (*all_philo)[i].id, (*all_philo)[i].left_fork, (*all_philo)[i].right_fork);
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
    printf("***ENTER INIT THREAD***\n");
    // printf("data %d\n", data->time_to_die);
    
    int i;
    t_philo *philo;

    i = 0;
    philo = data->philo;
    while (i < philo->data->nb_of_philo)
    {
   	printf("%d --> left: %d, right: %d -->\n", philo->id, philo->left_fork, philo->right_fork);
        if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
            return (err_msg(5));
        i++;
    }
    i = 0;
    while (i < philo->data->nb_of_philo)
    {
        if (pthread_join(philo[i].thread, NULL) != 0)
            return (err_msg(5));
        i++;
    }    
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
