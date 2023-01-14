/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:29:14 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/14 17:56:03 by tas              ###   ########.fr       */
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
	(void)argv;

    ft_memset(&data, 0, sizeof(t_data));
	if (!(argc == 5 || argc == 6))
		return(err_msg(0));
	if (arg_valid(argv) == 1)
		return(err_msg(4));
	init_param(&data, argv, argc);
	return (0);
}