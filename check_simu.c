/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:16:27 by tas               #+#    #+#             */
/*   Updated: 2023/01/31 13:54:47 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int check_death(t_data *data)
{
    if (get_time() - data->philo->last_meal >= data->time_to_die)
        data->is_dead = 1;
    return (0);    
}

/* Check si il y a un mort ou si le nb de repas a bien été pris --> stop la simulation */
void    *simulation_possible(void *d)
{
    (void)d;
    printf("JE SUPERVISE\n");
    int     i;
    t_data  *data;
    t_philo **all_philo;

    i = 0;
    data = d;
    all_philo = data->first_philo;
    
    pthread_mutex_lock(data->print_lock);
    pthread_mutex_lock(data->dead_lock);
    if (check_death(data) == 1)
    {
        pthread_mutex_unlock(data->print_lock);
        print_status('d', *all_philo, data);
        data->flag_simu = 1;
        exit(1);
    }
    pthread_mutex_lock(data->meals_lock);
    if (data->nb_of_meal == -1)
    {
        pthread_mutex_unlock(data->meals_lock);
        return (0);
    }
    while (all_philo[i])
    {
        pthread_mutex_unlock(data->meals_lock);
        if (all_philo[i]->meals_took != data->nb_of_meal)
            return (0);
        pthread_mutex_lock(data->meals_lock);
        i++;
    }
    pthread_mutex_unlock(data->print_lock);
    pthread_mutex_unlock(data->meals_lock);
    pthread_mutex_unlock(data->dead_lock);
    printf("All the philosophers have eat at least %d times\n", data->nb_of_meal);
    data->flag_simu = 1;
    exit(1);
    // return (0);
}