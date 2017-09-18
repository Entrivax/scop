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

int		parse_face(t_lst *splt, t_app *app, t_lst *faces)
{
	t_lst		*face;
	int			i;
	t_lst		*sl;
	t_vertex	*vertex;

	face = list_new();
	i = 0;
	while (++i < splt->size)
	{
		vertex = (t_vertex *)sec_malloc(sizeof(t_vertex));
		sl = split_keep_empty((char *)LGET(splt, i), '/');
		if (sl->size == 0 || sl->size >= 4)
			return (1);
		if (sl->size >= 1 && ft_isnumber(LGET(sl, 0)))
			vertex->v = (t_vec3 *)LGET(app->vertices, ft_atoi(LGET(sl, 0)) - 1);
		if (sl->size >= 2 && ft_isnumber(LGET(sl, 1)))
			vertex->uv = (t_vec2 *)LGET(app->uvs, ft_atoi(LGET(sl, 1)) - 1);
		if (sl->size >= 3 && ft_isnumber(LGET(sl, 2)))
			vertex->n = (t_vec3 *)LGET(app->normals, ft_atoi(LGET(sl, 2)) - 1);
		list_add(face, vertex);
		list_destroy_and_free_content(&sl, &free);
	}
	list_add(faces, face);
	return (0);
}

int		parse_split2(t_lst *splt, t_app *app, t_lst *faces)
{
	if (ft_strequ("vt", LGET(splt, 0)))
	{
		if (splt->size != 3 || !ft_isnumber(LGET(splt, 1)) ||
			!ft_isnumber(LGET(splt, 2)))
			return (1);
		list_add(app->uvs, n_vec2(ft_atof(LGET(splt, 1)),
			-ft_atof(LGET(splt, 2))));
	}
	else if (ft_strequ("f", LGET(splt, 0)))
	{
		if (splt->size < 4 || parse_face(splt, app, faces))
			return (1);
	}
	return (0);
}

int		parse_split(t_lst *splt, t_app *app, t_lst *faces)
{
	if (splt->size == 0)
		return (0);
	if (ft_strequ("v", LGET(splt, 0)))
	{
		if (splt->size != 4 || !ft_isnumber(LGET(splt, 1)) ||
			!ft_isnumber(LGET(splt, 2)) || !ft_isnumber(LGET(splt, 3)))
			return (1);
		list_add(app->vertices, n_vec3(ft_atof(LGET(splt, 1)),
			ft_atof(LGET(splt, 2)), ft_atof(LGET(splt, 3))));
	}
	else if (ft_strequ("vn", LGET(splt, 0)))
	{
		if (splt->size != 4 || !ft_isnumber(LGET(splt, 1)) ||
			!ft_isnumber(LGET(splt, 2)) || !ft_isnumber(LGET(splt, 3)))
			return (1);
		list_add(app->normals, n_vec3(ft_atof(LGET(splt, 1)),
			ft_atof(LGET(splt, 2)), ft_atof(LGET(splt, 3))));
	}
	else
		return (parse_split2(splt, app, faces));
	return (0);
}
