/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:29:46 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/23 15:47:46 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_time(time_t start)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000)+ (tv.tv_usec / 1000));
    // return ((tv.tv_sec * 1000)+ (tv.tv_usec / 1000) - start);
}

void	print_status(char *str, t_philo *philo, t_data *data)
{
	time_t timestamp; //le temps actuel depuis le debut

	timestamp = get_time - data->start_time;
	if (str == "fork")
		printf("%d %d %s\n", timestamp, philo->id, FORK);
	if (str == "eat")
		printf("%d %d %s\n", timestamp, philo->id, EAT);
	if (str == "sleep")
		printf("%d %d %s\n", timestamp, philo->id, SLEEP);
	if (str == "think")
		printf("%d %d %s\n", timestamp, philo->id, THINK);
	if (str == "died")
	{
		printf("%d %d %s\n", timestamp, philo->id, DIED);
		return (1);
	}	
	return (0);
}