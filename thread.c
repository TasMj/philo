/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:13:37 by tas               #+#    #+#             */
/*   Updated: 2023/01/15 15:30:20 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine()
{
    printf("test\n");
    return (0);
}


int    init_thread(t_data *data)
{
    int         i;
    int         nb_philo;
    pthread_t   t[data->nb_of_philo];

    i = 0;
    nb_philo = data->nb_of_philo;
    while (i < nb_philo)
    {
        if (pthread_create(t + i, NULL, &routine, NULL) != 0)
            return (err_msg(5));
        if (pthread_join(t[i], NULL) != 0)
            return (err_msg(5));
        i++;
    }
    return (0);
}
