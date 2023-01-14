/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:52:57 by tas               #+#    #+#             */
/*   Updated: 2023/01/14 13:13:23 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_msg(int n)
{
	write(1, "Error: ", 7);
	if (n == 0)
		write(1, ERR_ARG, ft_strlen(ERR_ARG));
	if (n == 1)
		write(1, ERR_ARG_DIGIT, ft_strlen(ERR_ARG_DIGIT));
	if (n == 2)
		write(1, ERR_ARG_OF, ft_strlen(ERR_ARG_OF));
    return (0);
}
