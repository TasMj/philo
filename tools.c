/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:29:46 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/24 21:09:22 by tas              ###   ########.fr       */
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

	timestamp = (long int)(get_time - data->start_time);
	if (s == 'f')
		printf("%ld %d %s\n", timestamp, philo->id, FORK);
	if (s == 'e')
		printf("%ld %d %s\n", timestamp, philo->id, EAT);
	if (s == 's')
		printf("%ld %d %s\n", timestamp, philo->id, SLEEP);
	if (s == 't')
		printf("%ld %d %s\n", timestamp, philo->id, THINK);
	if (s == 'd')
	{
		printf("%ld %d %s\n", timestamp, philo->id, DIED);
		return (1);
	}	
	return (0);
}