/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:17:29 by kmohamed          #+#    #+#             */
/*   Updated: 2023/04/22 19:41:01 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/memory.h"

// processname | philo_number | time_to_die | time_to_eat | time_to_sleep
void	input_read(char **argv, t_philosophers_env *env)
{
	if (!is_number(argv[1]))
		throw_error(ARG_ERROR, env);
	env->size = (size_t) ft_atoi(argv[1]);
	if (!is_number(argv[2]))
		throw_error(ARG_ERROR, env);
	env->time_to_die = ft_atoi(argv[2]);
	if (!is_number(argv[3]))
		throw_error(ARG_ERROR, env);
	env->time_to_eat = ft_atoi(argv[3]);
	if (!is_number(argv[4]))
		throw_error(ARG_ERROR, env);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		if (!is_number(argv[5]))
			throw_error(ARG_ERROR, env);
		env->number_of_meals = ft_atoi(argv[5]);
	}
}

void	get_philo_id(int *i)
{

	pthread_mutex_t lock;

	pthread_mutex_lock(&lock);
	printf("philo [%d]\n", *i);
	pthread_mutex_unlock(&lock);
}

void	create_philosophers(t_philosophers_env *env)
{
	int	i;

	env->philosophers = my_malloc(&env->memory_list, sizeof(t_philosopher));
	if (!env->philosophers)
		throw_error(HEAP_ERROR, env);
	i = -1;
	while (++i < (int) env->size)
	{
		env->philosophers[i].has_leftfork = 0;
		env->philosophers[i].has_rightfork = 0;
		env->philosophers[i].is_eating = 0;
		env->philosophers[i].last_meal = 0;
		env->philosophers[i].number_of_meals = 0;
		env->philosophers[i].time_to_die = env->time_to_die;
		env->philosophers[i].time_to_die = env->time_to_die;
	}
}

void	env_init(t_philosophers_env *env)
{
	int	i;

	env->chop_sticks = my_malloc(&env->memory_list , sizeof(pthread_mutex_t) * env->size);
	if (!env->chop_sticks)
		throw_error(HEAP_ERROR, env);
	env->number_of_meals = -1;
	env->philosopher_dead = 0;
	create_philosophers(env);
	i = -1;
	while (++i < (int) env->size)
		pthread_mutex_init(&env->chop_sticks[i], NULL);
}

int	main(int argc, char **argv)
{
	t_philosophers_env	env;

	env.memory_list = NULL;
	if (argc != 5 && argc != 6)
		throw_error(ARG_ERROR, &env);
	input_read(argv, &env);
	env_init(&env);
	exit_simulation(&env);
	return (0);
}
