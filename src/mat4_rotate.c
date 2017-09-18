/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_mat4			create_rot(float theta, t_vec3 axis)
{
	t_mat4	m;
	double	cost;
	double	sint;

	cost = cos(theta);
	sint = sin(theta);
	ft_bzero(&m, sizeof(t_mat4));
	m.m[0] = axis.x * axis.x * (1 - cost) + cost;
	m.m[1] = axis.x * axis.y * (1 - cost) - axis.z * sint;
	m.m[2] = axis.x * axis.z * (1 - cost) + axis.y * sint;
	m.m[4] = axis.x * axis.y * (1 - cost) + axis.z * sint;
	m.m[5] = axis.y * axis.y * (1 - cost) + cost;
	m.m[6] = axis.y * axis.z * (1 - cost) - axis.x * sint;
	m.m[8] = axis.x * axis.z * (1 - cost) - axis.y * sint;
	m.m[9] = axis.y * axis.z * (1 - cost) + axis.x * sint;
	m.m[10] = axis.z * axis.z * (1 - cost) + cost;
	m.m[15] = 1;
	return (m);
}

t_mat4			mat4_rotate(t_mat4 m, t_vec3 v)
{
	t_vec3	x;
	t_vec3	y;
	t_vec3	z;

	x.x = 1;
	x.y = 0;
	x.z = 0;
	y.x = 0;
	y.y = 1;
	y.z = 0;
	z.x = 0;
	z.y = 0;
	z.z = 1;
	return (mat4_mult(mat4_mult(mat4_mult(m, create_rot(v.x, x)),
		create_rot(v.y, y)), create_rot(v.z, z)));
}
