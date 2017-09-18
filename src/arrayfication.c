/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrayfication.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_vec2	*arrayfy_triangles_uv(t_lst *triangles)
{
	t_vec2		*uv;
	int			i;
	t_triangle	*triangle;

	uv = sec_malloc(sizeof(t_vec2) * triangles->size * 3);
	i = -1;
	while (++i < triangles->size)
	{
		triangle = ((t_triangle *)LGET(triangles, i));
		uv[i * 3] = *triangle->vertices[0].uv;
		uv[i * 3 + 1] = *triangle->vertices[1].uv;
		uv[i * 3 + 2] = *triangle->vertices[2].uv;
	}
	return (uv);
}

t_vec3	*arrayfy_triangles_vert(t_lst *triangles)
{
	t_vec3		*vertexes;
	int			i;
	t_triangle	*triangle;

	vertexes = sec_malloc(sizeof(t_vec3) * triangles->size * 3);
	i = -1;
	while (++i < triangles->size)
	{
		triangle = ((t_triangle *)LGET(triangles, i));
		vertexes[i * 3] = *triangle->vertices[0].v;
		vertexes[i * 3 + 1] = *triangle->vertices[1].v;
		vertexes[i * 3 + 2] = *triangle->vertices[2].v;
	}
	return (vertexes);
}
