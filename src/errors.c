/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmohamed <kmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:31:01 by kmohamed          #+#    #+#             */
/*   Updated: 2023/04/19 18:55:34 by kmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	throw_error(t_erros error)
{
	if (error == ARG_ERROR)
		printf("ARG_ERROR\n");
	exit (1);
}
