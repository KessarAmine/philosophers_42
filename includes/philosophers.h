/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:14:26 by kmohamed          #+#    #+#             */
/*   Updated: 2023/04/22 21:28:27 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_philosopher
{
	int					id;
	pthread_t			*thread_id;
	pthread_mutex_t		*leftfork;
	pthread_mutex_t		*rightfork;
	int					last_meal;
	int					is_eating;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					number_of_meals;
	t_philosophers_env	*shared_memory;
}				t_philosopher;

typedef	struct	s_philosophers_env
{
	void			*memory_blocks;
	t_philosopher	*philosophers;
	pthread_mutex_t	*chop_sticks;
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
	HEAP_ERROR
}				t_erros;

void		exit_simulation( t_philosophers_env *env);
void		throw_error(t_erros error, t_philosophers_env *env);
void		env_init(t_philosophers_env *env);
long int	ft_atoi(const char *str);
void		input_read(char **argv, t_philosophers_env *env);
int			is_number(char *av);
void		create_philosophers(t_philosophers_env *env);