/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_lst	*triangulate(t_lst *faces)
{
	int			face;
	t_lst		*face_vertices;
	int			last_vertex;
	t_lst		*triangles;
	t_triangle	*triangle;

	face = -1;
	triangles = list_new();
	while (++face < faces->size)
	{
		face_vertices = LGET(faces, face);
		last_vertex = 1;
		while (++last_vertex < face_vertices->size)
		{
			triangle = (t_triangle *)sec_malloc(sizeof(t_triangle));
			triangle->vertices[0] = *(t_vertex *)LGET(face_vertices, 0);
			triangle->vertices[1] = *(t_vertex *)LGET(face_vertices,
				last_vertex - 1);
			triangle->vertices[2] = *(t_vertex *)LGET(face_vertices,
				last_vertex);
			list_add(triangles, triangle);
		}
	}
	return (triangles);
}
