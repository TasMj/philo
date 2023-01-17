/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/01/17 14:01:01 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//gere thread par thread
int is_eating(t_philo *philo, t_data *data)
{
    int alive;
    
    if (data->meal == 0) // tt le monde a manger au moins x fois
        return (1);
    if (!data->meal || data->meal == data->max_meal) //first round
    {
        if (philo->philo_id % 2 == 0)
            usleep(50);
    }
    alive = get_time(data->start_time);
    if (alive < 0)
    {
        printf("%d %d died\n", alive, philo->philo_id);
        data->is_dead = 1;
        return (1);
    }
    printf("%d %d is eating\n", alive, philo->philo_id);
    usleep(data->time_to_eat * 1000);
    if (philo->philo_id == data->nb_of_philo)
        data->meal--;
    return (0);
}

int is_sleeping_then_thinking(t_philo *philo, t_data *data)
{
    int alive;
        
    alive = get_time(data->start_time) + 200;
    usleep(data->time_to_sleep * 1000);
    printf("%d %d is sleeping\n", alive, philo->philo_id);
    usleep(data->time_to_sleep * 1000);
    printf("%d %d is thinking\n", alive, philo->philo_id);
    return (0);
}

int is_dead(t_data *data)
{
    if (data->is_dead == 1)
        return (1);
    return (0);
}

void    *routine(t_philo *philo, t_data *data)
{
    is_eating(philo, data);
    if (is_dead(data) ==  1)
    {
        printf("%d %d died\n", get_time(data->start_time), philo->philo_id);
        return (1);
    }
    is_sleeping(philo, data);
    return (0);
}
