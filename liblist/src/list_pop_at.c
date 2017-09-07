/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pop_at.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

void	*list_pop_at(t_lst *list, int index)
{
	void	*content;

	content = LGET(list, index);
	list->size--;
	ft_memmove(list->content + index, list->content + index + 1,
		sizeof(void *) * (list->size - index));
	ft_bzero(list->content + list->size,
		sizeof(void *) * (list->current_allocated_size - list->size));
	return (content);
}
