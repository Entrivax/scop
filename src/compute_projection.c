/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_mat4	compute_projection(float near, float far, float aspect, float fov)
{
	float	zrange;
	float	tanhalffov;
	t_mat4	m;

	tanhalffov = tan((PI / 180.f) * fov / 2.f);
	zrange = near - far;
	ft_bzero(&m, sizeof(t_mat4));
	m.m[0] = 1.f / (tanhalffov * aspect);
	m.m[5] = 1.f / tanhalffov;
	m.m[10] = (-near - far) / zrange;
	m.m[11] = 2 * far * near / zrange;
	m.m[14] = 1.f;
	return (m);
}
