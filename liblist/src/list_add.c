/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

int		list_add(t_lst *list, void *content)
{
	void	*tmp;

	if (list->size + 1 > list->current_allocated_size)
	{
		if ((tmp = ft_memalloc(sizeof(void *) *
			list->current_allocated_size * 2)) == NULL)
			return (0);
		ft_memcpy(tmp, list->content, sizeof(void *) *
			list->current_allocated_size);
		free(list->content);
		list->content = tmp;
		list->current_allocated_size *= 2;
	}
	list->content[list->size] = content;
	list->size++;
	return (1);
}
