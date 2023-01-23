/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/01/23 15:51:42 by tas              ###   ########.fr       */
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
        if (&philo[i].meals_took != data->nb_of_meal)
            return (1);
        i++;
    }
    return (0);
}

void    *routine_one_philo(t_data *data)
{
    pthread_mutex_lock(data->forks_lock);
    printf("%d %d %s\n", 0, 1, FORK);
    usleep(data->time_to_die);
    printf("%d %d %s\n", data->time_to_die, 1, DIED);
    pthread_mutex_unlock(data->forks_lock);
}

//gere thread par thread
int eating(t_philo *philo, t_data *data)
{
    if (philo->meals_took == 0) //first round
    {
        if (philo->id % 2 == 0)
            usleep(100);
    }
    pthread_mutex_lock(&data->forks_lock[philo->left_fork]);
    print_status("fork", philo, data);
    pthread_mutex_lock(&data->forks_lock[philo->right_fork]);
    print_status("fork", philo, data);
    usleep(data->time_to_eat * 1000);
    print_status("eat", philo, data);
    pthread_mutex_unlock(&data->forks_lock[philo->left_fork]);
    pthread_mutex_unlock(&data->forks_lock[philo->right_fork]);
    philo->meals_took++;
    return (0);
}

int sleeping_and_thinking(t_philo *philo, t_data *data)
{
    usleep(data->time_to_sleep * 1000);
    print_status("sleep", philo, data);
    print_status("think", philo, data);
    get_time(data->start_time);
    return (0);
}

void    *routine(t_data *data)
{
    t_philo *philo;

    while (possible_to_continue(data, philo))
    {
        eating(&philo, data);
        sleeping_andthinking(&philo, data);
    }
    return (0);
}
