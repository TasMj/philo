/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:16:27 by tas               #+#    #+#             */
/*   Updated: 2023/02/06 19:34:54 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_simu(t_data *data)
{
    int res;
    pthread_mutex_lock(data->dead_lock);
    printf("change la valeur flag mort a %d\n\n", data->flag_simu);
    res = data->flag_simu;
    pthread_mutex_unlock(data->dead_lock);
    return (res);
}

// int incr_simu(t_data *data)
// {
//     pthread_mutex_lock(data->dead_lock);
//     data->flag_simu = 1;
//     pthread_mutex_unlock(data->dead_lock);
//     return (0);
// }

int check_time_death(t_data *data, t_philo *philo)
{
    if (((get_time() - data->start_time) - philo->last_meal) > data->time_to_die)
    {
        data->flag_simu = 1;
        return (1);
    }
    return (0);    
}

void    *check_death(void *d)
{
    int     i;
    t_data  *data;
    t_philo **philo;


    data = d;
    philo = data->first_philo;
    while (data->flag_simu == 0)
    {
        // pthread_mutex_lock(data->print_lock);
        i = 0;
        while (i < data->nb_of_philo)
        {
            if (check_time_death(data, philo[i]) == 1)
            {
                printf("%d passe par la\n\n\n", philo[i]->id);
                // pthread_mutex_lock(data->print_lock);
                print_status('d', philo[i], data);
                // pthread_mutex_unlock(data->print_lock);
                return (NULL);
            }
            i++;
        }
        // pthread_mutex_unlock(data->print_lock);
    }
    return (NULL);
}

void    *check_meals(void *d)
{
    int     i;
    t_data  *data;
    t_philo **philo;

    i = 0;
    data = d;
    philo = data->first_philo;
    while (data->flag_simu == 0)
    {
        if (data->nb_of_meal == -1)
            return (0);
        while (philo[i])
        {
            if ((philo[i]->meals_took < data->nb_of_meal))
                i = 0;
            i++;
        }
        data->flag_simu = 1;
        printf("\033[1;31mAll the philosophers have eaten at least %d times\033[0m\n", data->nb_of_meal);
        return (0);
    }
    return (0);
}