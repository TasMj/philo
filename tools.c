/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:29:46 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/27 01:53:16 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_time()
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	print_status(char s, t_philo *philo, t_data *data)
{
	time_t timestamp; //le temps actuel depuis le debut

	timestamp = (long int)(get_time() - data->start_time);
	if (s == 'f')
		printf("\033[1;33m%ld\033[0m %d \033[35m%s\033[0m\n", timestamp, philo->id, FORK);
	if (s == 'e')
		printf("\033[1;33m%ld\033[0m %d \033[36m%s\033[m\n", timestamp, philo->id, EAT);
	if (s == 's')
		printf("\033[1;33m%ld\033[0m %d \033[1;32m%s\033[0m\n", timestamp, philo->id, SLEEP);
	if (s == 't')
		printf("\033[1;33m%ld\033[0m %d \033[33m%s\033[0m\n", timestamp, philo->id, THINK);
	if (s == 'd')
	{
		printf("\033[1;33m%ld\033[0m %d %s\031[0m\n", timestamp, philo->id, DIED);
		return (1);
	}	
	return (0);
}