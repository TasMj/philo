/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/01/16 16:18:26 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//gere thread par thread
void    is_eating(t_philo *philo, t_data *data)
{
    int i;
    int alive;
    
    i = 0;
    if (data->meal == 0) //first round
    {
        while ()
        {
            if (philo->philo_id % 2 == 0)
                usleep(50);
            alive = 200 - get_time(data->start_time);
            if (alive < 0)
            {
                printf("%d %d died\n", alive, philo->philo_id);
                return (0);
            }
        }
        // 
        // 
    }
}

void    *routine()
{
    printf("test id");
    return (0);
    //mager
    //dormir
    //penser (pas besoin de temps precis pour ca)
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
        // philo->thread = &t[i];
        // printf(":%ln\n", philo->thread);
        i++;
    }
    return (0);
}
