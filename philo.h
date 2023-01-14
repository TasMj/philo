/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:27:57 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/14 17:53:08 by tas              ###   ########.fr       */
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

#define ERR_ARG "Not the right amount of arguments.\n"
#define ERR_ARG_DIGIT "You must enter only positif digits.\n"
#define ERR_ARG_OF "Problem overflow.\n"
#define ERR_NB_PHILO "You need to have at least 1 philosopher.\n"
#define ERR_ARGS_NO_VALID "Please enter:\n\t<nb of philosopher> <time to die> <time to eat> <time to sleep> <nb of meal (facultatif)>.\n"

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
int     ft_strlen(char *str);
int     ft_atoi(const char *nptr);

/*error*/
int     err_msg(int n);

/*init*/
int     check_args(char *argv);
int     arg_valid(char **argv);
int     init_param(t_data *data, char **argv, int argc);

#endif