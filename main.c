/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:29:14 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/14 17:29:01 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ss;
	size_t	i;

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

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	**philo;

	philo = NULL;
	ft_memset(&data, 0, sizeof(t_data));
	if (!(argc == 5 || argc == 6))
		return (err_msg(0));
	if (arg_valid(argv) == 1)
		return (err_msg(4));
	if (init_data(&data, argv, argc) != 0)
		return (0);
	init_mutex(&data);
	init_philo(philo, &data);
	if (data.nb_of_philo != 1)
		init_thread(&data);
	free_all(&data, philo);
	return (0);
}
