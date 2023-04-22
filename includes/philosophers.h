/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:14:26 by kmohamed          #+#    #+#             */
/*   Updated: 2023/04/22 22:11:50 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_philosopher
{
	int							id;
	pthread_t					*thread_id;
	pthread_mutex_t				*leftfork;
	pthread_mutex_t				*rightfork;
	int							last_meal;
	int							is_eating;
	int							time_to_die;
	int							time_to_sleep;
	int							time_to_eat;
	int							number_of_meals;
	struct	s_philosophers_env	*shared_memory;
}				t_philosopher;

typedef	struct	s_philosophers_env
{
	void			*memory_blocks;
	t_philosopher	*philosophers;
	pthread_mutex_t	*chop_sticks;
	pthread_mutex_t	*env_monitoring;
	size_t			size;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				philosopher_dead;
	int				time_starting;
}				t_philosophers_env;

typedef enum	s_erros
{
	ARG_ERROR,
	THREAD_ERROR,
	HEAP_ERROR,
	STARVING_ERROR
}				t_erros;

int			exit_simulation( t_philosophers_env *env);
int			throw_error(t_erros error, t_philosophers_env *env);
int			env_init(t_philosophers_env *env);
long int	ft_atoi(const char *str);
int			nput_read(char **argv, t_philosophers_env *env);
int			is_number(char *av);
int			create_philosophers(t_philosophers_env *env);

void		threads_start(t_philosophers_env *env);
void		threads_join(t_philosophers_env *env);
void		*philosophers_routine(t_philosopher *philo);
