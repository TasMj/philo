/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:33:05 by tas               #+#    #+#             */
/*   Updated: 2023/01/26 19:19:48 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*free philo*/
int free_philos(t_philo **philo)
{
    int i;

    i = 0;
    printf("%d\n" ,(*philo)[i].id);
    while (i < (*philo)[i].data->nb_of_philo)
    {
    printf("surf\n");
        free(philo[i]->data);
        free(philo[i]);
        i++;
    }
    free(philo);
    return (0);
}

/*free data*/
// int free_data(t_data *data)
// {
//     // free_philos(data->first_philo);
//     free(data->philo);
//     // free(data);
//     return (0);
// }

/*free mutex*/


/*free all at the end*/
// int free_all(t_data *data, t_philo **philo)
// {
//     free_data(data);
//     // free_philos(philo);
//     return (0);
// }