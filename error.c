/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:52:57 by tas               #+#    #+#             */
/*   Updated: 2023/01/14 17:54:49 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_msg(int n)
{	
	if (n == 4)
	{
		write(1, ERR_ARGS_NO_VALID, ft_strlen(ERR_ARGS_NO_VALID));
		return (1);	
	}
	write(1, "Error: ", 7);
	if (n == 0)
		write(1, ERR_ARG, ft_strlen(ERR_ARG));
	if (n == 1)
		write(1, ERR_ARG_DIGIT, ft_strlen(ERR_ARG_DIGIT));
	if (n == 2)
		write(1, ERR_ARG_OF, ft_strlen(ERR_ARG_OF));
	if (n == 3)
		write(1, ERR_NB_PHILO, ft_strlen(ERR_NB_PHILO));
    return (1);
}
