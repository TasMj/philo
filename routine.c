/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/02/07 10:07:13 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine_one_philo(void *d)
{
    t_philo *philo;

    philo = d;
    pthread_mutex_lock(&philo->data->forks_lock[0]);
    printf("\033[1;33m%ld\033[0m %d \033[35m%s\033[0m \U0001f374\n", get_time() - philo->data->start_time, 1, FORK);
    usleep(philo->data->time_to_die * 1000);
    printf("\033[1;33m%ld\033[0m %d \033[31m%s\033[0m \U0001f480\n", get_time() - philo->data->start_time, 1, DIED);
    pthread_mutex_unlock(&philo->data->forks_lock[0]);
    return (0);
}

int eat(t_philo *philo, t_data *data)
{
    if ((philo->meals_took == 0) && (philo->id % 2 == 0))
        usleep(200 * 1000);
    pthread_mutex_lock(&data->forks_lock[philo->left_fork]);
    if (check_simu(data) == 0)
        print_status('f', philo, data);
    pthread_mutex_lock(&data->forks_lock[philo->right_fork]);
    if (check_simu(data) == 0)
    {
        print_status('f', philo, data);
        print_status('e', philo, data);
    }
    usleep(data->time_to_eat * 1000);
    pthread_mutex_unlock(&data->forks_lock[philo->right_fork]);
    pthread_mutex_unlock(&data->forks_lock[philo->left_fork]);
    philo->meals_took++;
    return (0);
}

int sleep_and_think(t_philo *philo, t_data *data)
{
    if (check_simu(data) == 0)
        print_status('s', philo, data);
    usleep(data->time_to_sleep * 1000);
    if (check_simu(data) == 0)
        print_status('t', philo, philo->data);
    return (0);
}

void    *routine(void *d)
{
    t_philo  *philo;
    philo = d;
    while (check_simu(philo->data) == 0)
    {
        // if(philo->data->flag_simu != 1 && (philo->meals_took < philo->data->nb_of_meal 
                // || philo->data->nb_of_meal == -1))
            eat(philo, philo->data);
        // if(philo->data->flag_simu != 1 && (philo->meals_took < philo->data->nb_of_meal 
                // || philo->data->nb_of_meal == -1))
            sleep_and_think(philo, philo->data);
    }
    return (0);
}
