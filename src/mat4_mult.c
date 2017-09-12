/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_mat4	mat4_mult(t_mat4 m1, t_mat4 m2)
{
	t_mat4	res;
	int		a;
	int		b;
	int		i;
	float	tmp;

	ft_bzero(&res, sizeof(t_mat4));
	a = -1;
	while (++a < 4)
	{
		b = -1;
		while (++b < 4)
		{
			tmp = 0;
			i = -1;
			while (++i < 4)
				tmp += m1.m[i + b * 4] * m2.m[a + i * 4];
			res.m[a + b * 4] = tmp;
		}
	}
	return (res);
}
