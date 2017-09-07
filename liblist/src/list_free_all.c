/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free_all.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

void	list_free_all(t_lst *list, void (*f)(void *content))
{
	int		i;
	int		size;

	i = 0;
	size = list->size;
	while (i < size)
	{
		f(LGET(list, i));
		i++;
	}
}
