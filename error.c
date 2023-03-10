/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:52:57 by tas               #+#    #+#             */
/*   Updated: 2023/02/17 17:56:58 by tmejri           ###   ########.fr       */
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
	if (n == 5)
		write(1, ERR_THREAD, ft_strlen(ERR_THREAD));
	if (n == 6)
		write(1, ERR_MALLOC, ft_strlen(ERR_MALLOC));
	if (n == 7)
		write(1, ERR_MUTEX, ft_strlen(ERR_MUTEX));
	if (n == 8)
		write(1, ERR_NO_MEAL, ft_strlen(ERR_NO_MEAL));
	return (1);
}
