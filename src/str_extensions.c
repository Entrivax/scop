/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

char	*str_alloc_cpy(char *src, size_t start, size_t length)
{
	char	*dst;
	size_t	i;

	dst = (char *)sec_malloc(length + 1);
	i = 0;
	while (i < length)
	{
		dst[i] = src[start + i];
		i++;
	}
	return (dst);
}

t_lst	*split_keep_empty(char *str, char sep)
{
	int		start;
	int		i;
	char	c;
	t_lst	*lst;

	i = -1;
	c = 1;
	start = 0;
	lst = list_new();
	while (str[++i])
		if (str[i] == sep)
		{
			list_add(lst, str_alloc_cpy(str, start, i - start - 1 + c));
			c = 0;
			start = i + 1;
		}
	list_add(lst, str_alloc_cpy(str, start, i - start));
	return (lst);
}

t_lst	*split(char *str, char sep)
{
	int		ind[2];
	char	cutting;
	t_lst	*lst;

	ind[0] = -1;
	cutting = 0;
	ind[1] = 0;
	lst = list_new();
	while (str[++ind[0]])
		if (!cutting && str[ind[0]] == sep)
			continue;
		else if (!cutting && str[ind[0]] != sep)
		{
			cutting = 1;
			ind[1] = ind[0];
			continue;
		}
		else if (cutting && str[ind[0]] == sep)
		{
			cutting = 0;
			list_add(lst, str_alloc_cpy(str, ind[1], ind[0] - ind[1]));
		}
	if (cutting)
		list_add(lst, str_alloc_cpy(str, ind[1], ind[0] - ind[1]));
	return (lst);
}
