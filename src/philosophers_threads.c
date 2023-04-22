/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_threads.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:12:21 by kmohamed          #+#    #+#             */
/*   Updated: 2023/04/22 21:28:30 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/memory.h"

void	*philosophers_routine(t_philosopher *philo)
{
	while (philo->shared_memory->philosopher_dead == 0)
	{
		if (philosopher_is_dead(philo))
			return (0);
		philosopher_takes_forks(philo);
		if (philosopher_is_dead(philo))
		{
			pthread_mutex_unlock(philo->leftfork);
			pthread_mutex_unlock(philo->rightfork);
			return (0);
		}
		philosophers_is_eating(philo);
		if (philosopher_is_dead(philo))
			return (0);
		philosophers_is_sleeping(philo);
		if (philosopher_is_dead(philo))
			return (0);
		philosophers_is_thinking(philo);
	}
	return (0);
}

void	join_threads(t_philosophers_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		pthread_join(env->philosophers[i].thread_id, NULL);
		i++;
	}
}

void	begin_philosophers_routine(t_philosophers_env *env)
{
	int	i;

	i = 0;
	env->time_starting = get_time();
	while (i < env->size)
	{
		pthread_create(&env->philosophers[i].thread_id,
			NULL, &philosophers_routine, (void *)&env->philosophers[i]);
		i++;
	}
	i = -1;
	while (++i < env->size)
		pthread_join(env->philosophers[i].thread_id, NULL);
}
