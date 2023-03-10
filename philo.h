/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmejri <tmejri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:27:57 by tmejri            #+#    #+#             */
/*   Updated: 2023/02/17 18:25:55 by tmejri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/******************************************************************************/
/*                                includes                                    */
/******************************************************************************/

# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

/******************************************************************************/
/*                                  macros                                    */
/******************************************************************************/

/*Errors*/
# define ERR_ARG "Not the right amount of arguments.\n"
# define ERR_ARG_DIGIT "You must enter only positif digits. Be careful with \
overflow.\n"
# define ERR_ARG_OF "Problem overflow.\n"
# define ERR_NB_PHILO "You need to have at least 1 philosopher.\n"
# define ERR_ARGS_NO_VALID "Please enter:\n\t<nb of philosopher> <time to die> \
<time to eat> <time to sleep> <nb of meal (facultatif)>.\n"
# define ERR_THREAD "Failed to create thread.\n"
# define ERR_MALLOC "Malloc failled.\n"
# define ERR_MUTEX "Mutex initialisation failled.\n"
# define ERR_NO_MEAL "The simulation will not start, because they have already \
eaten 0 meal.\n"

/*Philo status*/
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

/*constante*/
# define MAX 2147483647

/******************************************************************************/
/*                               structures                                   */
/******************************************************************************/

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	time_t			start_time;
	int				nb_of_meal;
	int				flag_simu;
	pthread_mutex_t	*forks_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	struct s_philo	**first_philo;
	pthread_t		watch_death;
	pthread_t		watch_meals;
}t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_data			*data;
	int				meals_took;
	int				right_fork;
	int				left_fork;
	time_t			last_meal;
}t_philo;

/******************************************************************************/
/*                               functions                                    */
/******************************************************************************/

/*check simu*/
int			check_simu(t_data *data);
int			incr_simu(t_data *data);
int			check_time_death(t_data *data, t_philo *philo);
void		*check_death(void *d);
void		*check_meals(void *d);

/*error*/
int			err_msg(int n);

/*free*/
int			free_philos(t_philo **philo, t_data *data);
int			free_data(t_data *data);
void		destroy_mutex(t_data *data);
int			free_all(t_data *data, t_philo **philo);

/*init*/
int			init_data(t_data *data, char **argv, int argc);
int			fill_philo(t_philo **philo, t_data *data, int i);
int			init_only_one_philo(t_philo **philo, t_data *data);
int			init_philo(t_philo **philo, t_data *data);
int			init_thread(t_data *data);
int			init_mutex(t_data *data);
int			join_thread(t_data *data);

/*parsing*/
int			check_digit(char *str);
int			check_args(char *argv);
int			arg_valid(char **argv);
int			ft_strlen(char *str);
long long	ft_atoi(const char *nptr);

/*tools*/
int			get_time(void);
int			print_status(char s, t_philo *philo, t_data *data);
int			u_sleep(t_data *data, time_t time);

/*routine*/
void		fork_process(t_philo *philo, t_data *data);
int			sleep_and_think(t_philo *philo, t_data *data);
void		*routine_one_philo(void *d);
int			even(t_philo *philo, t_data *data);
int			odd(t_philo *philo, t_data *data);
void		*routine(void *data);

#endif