/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:03:57 by tas               #+#    #+#             */
/*   Updated: 2023/01/23 11:06:26 by tas              ###   ########.fr       */
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

int ft_strlen(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
        i++;
    return (i);
}

int	ft_atoi(const char *nptr)
{
	int		res;
	int		i;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - 48);
		i++;
	}
	return (res * sign);
}