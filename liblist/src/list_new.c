/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

t_lst	*list_new(void)
{
	return (list_new_with_alloc_size(LIST_BASE_SIZE));
}

t_lst	*list_new_with_alloc_size(int size)
{
	t_lst	*list;

	if ((list = ft_memalloc(sizeof(t_lst))) == NULL)
		return (NULL);
	list->size = 0;
	if ((list->content = ft_memalloc(sizeof(void *) * size)) == NULL)
	{
		free(list);
		return (NULL);
	}
	list->current_allocated_size = size;
	return (list);
}
