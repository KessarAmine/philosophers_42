/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 22:00:32 by kmohamed          #+#    #+#             */
/*   Updated: 2023/04/22 22:20:38 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/memory.h"

int		philo_starving(t_philosopher *philo)
{
    struct timeval current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_usec - philo->shared_memory->time_starting > philo->time_to_die)
	{
		philo->shared_memory->philosopher_dead = 1;
		printf("%d %d died\n", current_time.tv_usec - philo->shared_memory->time_starting, philo->id);
		return (STARVING_ERROR);
	}
	else
		return (0);
}

int		philo_isdead(t_philosophers_env *env)
{
	int	i;

	i = -1;
	while (++i < env->size)
		if (philo_starving(&env->philosophers[i]) ==  STARVING_ERROR)
			return (throw_error(STARVING_ERROR, env));
	return (1);
}

void    *scheduler_routine(t_philosophers_env *env)
{
	while (1)
	{
		pthread_mutex_lock(env->env_monitoring);
		if (philo_isdead(env) == STARVING_ERROR)
		{
			usleep(100);
			pthread_mutex_unlock(env->env_monitoring);
			return (NULL);
		}
		pthread_mutex_unlock(env->env_monitoring);
		usleep(200);
	}
}

