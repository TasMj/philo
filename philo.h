/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tas <tas@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:27:57 by tmejri            #+#    #+#             */
/*   Updated: 2023/01/31 13:53:03 by tas              ###   ########.fr       */
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
#include <stdlib.h>

/******************************************************************************/
/*                                  macros                                    */
/******************************************************************************/

/*Errors*/
#define ERR_ARG "Not the right amount of arguments.\n"
#define ERR_ARG_DIGIT "You must enter only positif digits.\n"
#define ERR_ARG_OF "Problem overflow.\n"
#define ERR_NB_PHILO "You need to have at least 1 philosopher.\n"
#define ERR_ARGS_NO_VALID "Please enter:\n\t<nb of philosopher> <time to die> <time to eat> <time to sleep> <nb of meal (facultatif)>.\n"
#define ERR_THREAD "Failed to create thread.\n"
#define ERR_MALLOC "Malloc failled\n"
#define ERR_MUTEX "Mutex initialisation failled\n"

/*Philo status*/
#define FORK "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIED "died"

#define MAX 2147483647

/******************************************************************************/
/*                               structures                                   */
/******************************************************************************/

typedef struct s_data
{
    int             nb_of_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    time_t          start_time;
    int             nb_of_meal;
    int             is_dead;
    int             flag_simu;
    pthread_mutex_t *forks_lock;

    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meals_lock;
    pthread_mutex_t *print_lock;
    
    
    struct s_philo  *philo;
    struct s_philo  **first_philo;
    pthread_t       supervisor;
}t_data;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    t_data          *data;
    int             meals_took;
    int             right_fork;
    int             left_fork;
    time_t          last_meal;
}t_philo;

/******************************************************************************/
/*                               functions                                    */
/******************************************************************************/

/*parsing*/
int     check_digit(char *str);
int     check_args(char *argv);
int     arg_valid(char **argv);
int     ft_strlen(char *str);
int     ft_atoi(const char *nptr);

/*tools*/
int     get_time();
int     print_status(char s, t_philo *philo, t_data *data);

/*error*/
int     err_msg(int n);

/*init*/
int     init_data(t_data *data, char **argv, int argc);
int     init_philo(t_philo **philo,t_data *data);
int init_thread(t_data *data);

int     init_mutex(t_data *data);

/*routine*/
int     possible_to_continue(t_data *data);
int     eat(t_philo *philo, t_data *data);
int     sleep_and_think(t_philo *philo, t_data *data);
void    *simulation_possible(void *d);
void    *routine_one_philo(void *d);
void    *routine(void *data);

/*free*/
int     free_data(t_data *data);
int     free_philos(t_philo **philo);


#endif