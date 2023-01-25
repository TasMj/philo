/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:29:14 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/24 21:43:03 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char    *ss;
	size_t  i;

	i = 0;
	ss = (char *)s;
	while (i < n)
	{
		ss[i] = (char)c;
		i++;
	}
	s = (void *)ss;
	return (s);
}

int main(int argc, char **argv)
{
    t_data  data;
	t_philo	philo;
	
    ft_memset(&data, 0, sizeof(t_data));
    ft_memset(&philo, 0, sizeof(t_philo));
	if (!(argc == 5 || argc == 6))
		return(err_msg(0));
	if (arg_valid(argv) == 1)
		return(err_msg(4));
	init_data(&data, argv, argc);
	init_mutex(&data);
	init_philo(&philo, &data);
	// printf("ttd %d, tte %d, tts %d\n", data.time_to_die, data.time_to_eat, data.time_to_sleep);
	// printf("%d --> left: %d, right: %d\n", philo.id, philo.left_fork, philo.right_fork);
	// init_thread(&data);
	printf("\n\nEXIT MAIN\n");
	return (0);
}