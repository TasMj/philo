/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:30:56 by tas               #+#    #+#             */
/*   Updated: 2023/01/17 13:48:32 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_digit(char *str)
{
    int i;

    i = 0;
    if (ft_strlen(str) == 0)
        return (1);
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (1);
        i++;
    }
    return (0);
}

int check_args(char *argv)
{
    int n;
    
    n = ft_atoi(argv);
    if ((check_digit(argv) == 1) || n < 0)
        return (err_msg(1));
    if (n > MAX)
        return (err_msg(2));
    return (0);
}

int arg_valid(char **argv)
{
    int i;
    int c = 0;
    
    i = 1;
    while (argv[i])
    {
        if (check_args(argv[i]) == 1)
            c++;
        i++;
    }
    if (c != 0)
        return (1);
    return (0);
}

int init_param(t_data *data, char **argv, int argc)
{
    data->nb_of_philo = ft_atoi(argv[1]);
    if (data->nb_of_philo == 0)
        return(err_msg(3));
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->start_time = get_time(data->start_time);
    data->is_dead = 1;
    if (argc == 6)
    {
        data->meal = ft_atoi(argv[5]);
        data->max_meal = data->meal;   
    }
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
        // philo->thread = &t[i];
        // printf(":%ln\n", philo->thread);
        i++;
    }
    return (0);
}