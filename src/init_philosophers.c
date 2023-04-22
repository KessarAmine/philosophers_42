/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:17:29 by kmohamed          #+#    #+#             */
/*   Updated: 2023/04/22 22:18:41 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/memory.h"

//	static :input syntaxe:
//		processname | philo_number | time_to_die | time_to_eat | time_to_sleep
// 	rightfork = chop_sticks[(i + 1) % env->size] because it is a cercular table
int	input_read(char **argv, t_philosophers_env *env)
{
	if (!is_number(argv[1]))
		return (throw_error(ARG_ERROR, env));
	env->size = (size_t) ft_atoi(argv[1]);
	if (!is_number(argv[2]))
		return (throw_error(ARG_ERROR, env));
	env->time_to_die = ft_atoi(argv[2]);
	if (!is_number(argv[3]))
		return (throw_error(ARG_ERROR, env));
	env->time_to_eat = ft_atoi(argv[3]);
	if (!is_number(argv[4]))
		return (throw_error(ARG_ERROR, env));
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		if (!is_number(argv[5]))
			return (throw_error(ARG_ERROR, env));
		env->number_of_meals = ft_atoi(argv[5]);
	}
	return (0);
}

int	create_philosophers(t_philosophers_env *env)
{
	int	i;

	env->philosophers = my_malloc(&env->memory_blocks, sizeof(t_philosopher));
	if (!env->philosophers)
		return (throw_error(HEAP_ERROR, env));
	i = -1;
	while (++i < (int) env->size)
	{
		env->philosophers[i].id = i + 1;
		env->philosophers[i].leftfork = &env->chop_sticks[i];
		env->philosophers[i].rightfork = &env->chop_sticks[(i + 1) % env->size];
		env->philosophers[i].is_eating = 0;
		env->philosophers[i].last_meal = 0;
		env->philosophers[i].number_of_meals = 0;
		env->philosophers[i].time_to_die = env->time_to_die;
		env->philosophers[i].time_to_eat = env->time_to_eat;
		env->philosophers[i].time_to_sleep = env->time_to_sleep;
		env->philosophers[i].shared_memory = env;
	}
	return (0);
}

int	env_init(t_philosophers_env *env)
{
	int	i;

	env->chop_sticks = my_malloc(&env->memory_blocks , sizeof(pthread_mutex_t) * env->size);
	if (!env->chop_sticks)
		return (throw_error(HEAP_ERROR, env));
	env->number_of_meals = -1;
	env->philosopher_dead = 0;
	if (create_philosophers(env))
		return (1);
	i = -1;
	while (++i < (int) env->size)
		pthread_mutex_init(&env->chop_sticks[i], NULL);
	pthread_mutex_init(&env->env_monitoring, NULL);
	return (0);
}

//	first we init our envirment and prepare our memory_blocks
//	we create the philosophers threads and the needed mutexes
//	we start the scheduler
int	main(int argc, char **argv)
{
	t_philosophers_env	env;

	env.memory_blocks = NULL;
	if (argc != 5 && argc != 6)
		return (throw_error(ARG_ERROR, &env));
	if (input_read(argv, &env) || env_init(&env))
		return (1);
	return (exit_simulation(&env));
}
