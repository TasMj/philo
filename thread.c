/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/01/15 16:36:43 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine()
{
    printf("test id");
    return (0);
}

int    init_thread(t_data *data)
{
    int         i;
    int         nb_philo;
    pthread_t   t[data->nb_of_philo];
    t_philo     philo[data->nb_of_philo];

    i = 0;
    nb_philo = data->nb_of_philo;
    while (i < nb_philo)
    {
        if (pthread_create(t + i, NULL, &routine, NULL) != 0)
            return (err_msg(5));
        if (pthread_join(t[i], NULL) != 0)
            return (err_msg(5));
        philo->philo_id = i + 1;
        printf(":%d\n", philo->philo_id);
        // philo->thread = ;
        i++;
    }
    return (0);
}
