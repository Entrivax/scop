/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void	compute_obj_translation_minmax(t_vec3 *v, t_vec3 *minmax)
{
	if (v->x < minmax[0].x)
		minmax[0].x = v->x;
	else if (v->x > minmax[1].x)
		minmax[1].x = v->x;
	if (v->y < minmax[0].y)
		minmax[0].y = v->y;
	else if (v->y > minmax[1].y)
		minmax[1].y = v->y;
	if (v->z < minmax[0].z)
		minmax[0].z = v->z;
	else if (v->z > minmax[1].z)
		minmax[1].z = v->z;
}

void	compute_obj_translation(t_app *app)
{
	int		i;
	t_vec3	v;
	t_vec3	minmax[2];

	if (app->triangles->size == 0)
		return ;
	minmax[0] = app->vertex_array[0];
	minmax[1] = app->vertex_array[0];
	i = 0;
	while (++i < app->triangles->size * 3)
	{
		v = app->vertex_array[i];
		compute_obj_translation_minmax(&v, minmax);
	}
	app->object_trans.x = -(minmax[0].x + minmax[1].x) / 2.f;
	app->object_trans.y = -(minmax[0].y + minmax[1].y) / 2.f;
	app->object_trans.z = -(minmax[0].z + minmax[1].z) / 2.f;
}
