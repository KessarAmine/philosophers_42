/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:17:29 by kmohamed          #+#    #+#             */
/*   Updated: 2023/04/22 13:57:18 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/memory.h"

// processname | philo_number | time_to_die | time_to_eat | time_to_sleep
void	input_read(char **argv, t_philosophers_env *env)
{
	if (!is_number(argv[1]))
		throw_error(ARG_ERROR);
	env->size = (size_t) ft_atoi(argv[1]);
	if (!is_number(argv[2]))
		throw_error(ARG_ERROR);
	env->time_to_die = ft_atoi(argv[2]);
	if (!is_number(argv[3]))
		throw_error(ARG_ERROR);
	env->time_to_eat = ft_atoi(argv[3]);
	if (!is_number(argv[4]))
		throw_error(ARG_ERROR);
	env->time_to_sleep = ft_atoi(argv[4]);
}

void	get_philo_id(int *i)
{

	pthread_mutex_t lock;

	pthread_mutex_lock(&lock);
	printf("philo [%d]\n", *i);
	pthread_mutex_unlock(&lock);
}

void	create_philosopher(long thread_id, t_philosophers_env *env)
{
	t_philosopher *philosopher;

	philosopher = my_malloc(&env->memory_list, sizeof(t_philosopher));
	philosopher->has_leftfork = 0;
	philosopher->has_rightfork = 0;
	philosopher->is_eating = 0;
	philosopher->last_meal = 0;
	philosopher->number_of_meals = 0;
	philosopher->thread_id = thread_id;
	philosopher->time_to_die = env->time_to_die;
	philosopher->time_to_die = env->time_to_die;
}

void	env_init(t_philosophers_env *env)
{
	int	i;

	i = -1;
	while (++i < (int) env->size)
	{

		if (pthread_create(&env->list[i], NULL, (void *)&get_philo_id, &i) != 0)
			throw_error(THREAD_ERROR);
		create_philosopher((long) env->list[i], env);
	}
	i = -1;
	while (++i < (int) env->size)
		pthread_join(env->list[i], NULL);
}

int	main(int argc, char **argv)
{
	t_philosophers_env	env;

	env.memory_list = NULL;
	if (argc != 5)
		throw_error(ARG_ERROR);
	input_read(argv, &env);
	env.list = my_malloc(&env.memory_list , sizeof(pthread_t) * env.size);
	env.chop_sticks = my_malloc(&env.memory_list , sizeof(pthread_mutex_t) * env.size);
	env_init(&env);
	// free_all_mem(&env.memory_list);
	system("leaks philosophers");
	return (0);
}
