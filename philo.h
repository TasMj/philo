/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:27:57 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/16 16:07:14 by tmejri           ###   ########.fr       */
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
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

/******************************************************************************/
/*                                  macro                                     */
/******************************************************************************/

#define ERR_ARG "Not the right amount of arguments.\n"
#define ERR_ARG_DIGIT "You must enter only positif digits.\n"
#define ERR_ARG_OF "Problem overflow.\n"
#define ERR_NB_PHILO "You need to have at least 1 philosopher.\n"
#define ERR_ARGS_NO_VALID "Please enter:\n\t<nb of philosopher> <time to die> <time to eat> <time to sleep> <nb of meal (facultatif)>.\n"
#define ERR_THREAD "Failed to create thread.\n"

#define MAX 2147483647

/******************************************************************************/
/*                               structures                                   */
/******************************************************************************/

typedef struct s_data
{
    int         nb_of_philo; //also nb of fork
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    time_t      start_time;
    int         meal;
    
}t_data;

typedef struct s_philo
{
    int         philo_id;
    pthread_t   *thread;
    t_data      *data;
    
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

/*thread*/
int     init_thread(t_data *data);
void    *routine();


#endif