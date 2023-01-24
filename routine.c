/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/01/24 21:12:49 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int possible_to_continue(t_data *data, t_philo *philo)
{
    int i = 0;

    if (data->is_dead == 1)
        return (1);
    if (data->nb_of_meal == -1)
        return (0);
    while (&philo[i])
    {
        if (philo[i].meals_took != data->nb_of_meal)
            return (0);
        i++;
    }
    printf("All the philosophers have eat at least %d times\n", data->nb_of_meal);
    return (1);
}

void    *routine_one_philo(void *d)
{
    t_data *data;

    data = d;
    // pthread_mutex_lock(data->forks_lock);
    printf("%ld %d %s\n", get_time() - data->start_time, 1, FORK);
    usleep(data->time_to_die * 1000);
    // printf("%d %d %s\n", data->time_to_die, 1, DIED);
    printf("%ld %d %s\n", get_time() - data->start_time , 1, DIED);
    // pthread_mutex_unlock(data->forks_lock);
    return (0);
}

//gere thread par thread
int eat(t_philo *philo, t_data *data)
{
    printf("routine: %d", philo->id);
    if (philo->meals_took == 0)//first round
    {
        if (philo->id % 2 == 0)
            usleep(100);
    }
    pthread_mutex_lock(&data->forks_lock[philo->left_fork]);
    print_status('f', philo, data);
    pthread_mutex_lock(&data->forks_lock[philo->right_fork]);
    print_status('f', philo, data);
    usleep(data->time_to_eat * 1000);
    print_status('e', philo, data);
    pthread_mutex_unlock(&data->forks_lock[philo->left_fork]);
    pthread_mutex_unlock(&data->forks_lock[philo->right_fork]);
    philo->meals_took++;
    return (0);
}

int sleep_and_think(t_philo *philo, t_data *data)
{
    usleep(data->time_to_sleep * 1000);
    print_status('s', philo, data);
    print_status('t', philo, data);
    get_time(data->start_time);
    return (0);
}

void    *routine(void *d)
{
    t_philo *philo;
    
    philo = (t_philo *)d;
    while (possible_to_continue(philo->data, philo))
    {
        eat(philo, philo->data);
        sleep_and_think(philo, philo->data);
    }
    return (0);
}
