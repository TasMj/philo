/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/01/27 01:33:25 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine_one_philo(void *d)
{
    t_philo *philo;

    philo = d;
    pthread_mutex_lock(&philo->data->forks_lock[0]);
    printf("%ld   %d %s\n", get_time() - philo->data->start_time, 1, FORK);
    usleep(philo->data->time_to_die * 1000);
    printf("%ld %d %s\n", get_time() - philo->data->start_time, 1, DIED);
    pthread_mutex_unlock(&philo->data->forks_lock[0]);
    return (0);
}

/*no death and philo has eaten all their meal*/
int possible_to_continue(t_data *data)
{
    t_philo **all_philo;
    int i = 0;

    all_philo = data->first_philo;
    if (data->is_dead == 1)
        return (1);
    if (data->nb_of_meal == -1)
        return (0);
    while (all_philo[i])
    {
        if (all_philo[i]->meals_took != data->nb_of_meal)
            return (0);
        i++;
    }
    printf("All the philosophers have eat at least %d times\n", data->nb_of_meal);
    return (1);
}

//gere thread par thread
int eat(t_philo *philo, t_data *data)
{
    if ((philo->meals_took == 0) && (philo->id % 2 == 0))//first round
        usleep(100);
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
    // printf(" in the routine bro\n");
    t_philo  *philo;

    philo = d;
    // printf("[%d] --> left: [%d], right: [%d]\n", philo->id, philo->left_fork, philo->right_fork);
    while (possible_to_continue(philo->data) == 0)
    {
        eat(philo, philo->data);
        sleep_and_think(philo, philo->data);
    }
    return (0);
}
