/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:27:57 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/14 13:19:48 by tas              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

/******************************************************************************/
/*                                  macro                                     */
/******************************************************************************/

#define ERR_ARG "Not the right amount of arguments\n"
#define ERR_ARG_DIGIT "You must enter only positif digits\n"
#define ERR_ARG_OF "Problem overflow\n"

#define MAX 2147483647

/******************************************************************************/
/*                               structures                                   */
/******************************************************************************/

typedef struct s_data
{
    int nb_of_philo; //also nb of fork
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int start_time;
    int meal;
    
}t_data;

typedef struct s_philo
{
    int     philo_id;
    t_data  *data;
    
}t_philo;


/******************************************************************************/
/*                               functions                                    */
/******************************************************************************/

/*tools*/
int ft_strlen(char *str);
int	ft_atoi(const char *nptr);

/*error*/
int	err_msg(int n);


#endif