/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_missing_uvs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void	compute_missing_uvs(t_app *app)
{
	int			i[2];
	t_vec2		*uv;
	t_triangle	*triangle;

	i[0] = -1;
	while (++i[0] < app->triangles->size)
	{
		triangle = LGET(app->triangles, i[0]);
		i[1] = -1;
		while (++i[1] < 3)
		{
			if (triangle->vertices[i[1]].uv != NULL)
				continue ;
			uv = n_vec2(triangle->vertices[i[1]].v->z,
				-triangle->vertices[i[1]].v->y);
			list_add(app->uvs, uv);
			triangle->vertices[i[1]].uv = uv;
		}
	}
}
