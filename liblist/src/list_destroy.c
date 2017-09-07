/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"

void	list_destroy(t_lst **list)
{
	if ((*list)->content != NULL)
		free((*list)->content);
	(*list)->content = NULL;
	free(*list);
}

void	list_destroy_and_free_content(t_lst **list, void (*f)(void *content))
{
	list_free_all(*list, f);
	list_destroy(list);
}
