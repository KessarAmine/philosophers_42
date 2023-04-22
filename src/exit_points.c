/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_points.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:31:01 by kmohamed          #+#    #+#             */
/*   Updated: 2023/04/22 21:39:54 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/memory.h"

int	throw_error(t_erros error, t_philosophers_env *env)
{
	if (error == ARG_ERROR)
		printf("ARG_ERROR\n");
	if (error == HEAP_ERROR)
		printf("HEAP_ERROR\n");
	if (error == THREAD_ERROR)
		printf("THREAD_ERROR\n");
	free_all_mem(&env->memory_blocks);
	return (1);
}

int	exit_simulation(t_philosophers_env *env)
{
	free_all_mem(&env->memory_blocks);
	return(0);
}
