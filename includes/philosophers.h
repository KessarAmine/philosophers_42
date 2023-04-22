/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:14:26 by kmohamed          #+#    #+#             */
/*   Updated: 2023/04/22 13:50:15 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef	struct	s_philosophers_env
{
	void			*memory_list;
	pthread_mutex_t	*chop_sticks;
	pthread_t		*list;
	size_t			size;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}				t_philosophers_env;

typedef struct	s_philosopher
{
	long	thread_id;
	int		has_leftfork;
	int		has_rightfork;
	int		last_meal;
	int		is_eating;
	int		time_to_die;
	int		time_to_sleep;
	int		time_to_eat;
	int		number_of_meals;
}				t_philosopher;

typedef enum	s_erros
{
	ARG_ERROR,
	THREAD_ERROR
}				t_erros;

void		throw_error(t_erros error);
void		env_init(t_philosophers_env *env);
long int	ft_atoi(const char *str);
void		input_read(char **argv, t_philosophers_env *env);
int			is_number(char *av);
void		create_philosopher(long thread_id, t_philosophers_env *env);