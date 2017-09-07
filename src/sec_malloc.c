/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 15:16:44 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:21:26 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void	safe_exit(void)
{
	exit(1);
}

void	*sec_malloc(size_t size)
{
	void	*mem;

	if ((mem = ft_memalloc(size)) == NULL)
	{
		ft_putendl("Error happened during memory allocation. Exiting...");
		safe_exit();
	}
	return (mem);
}
