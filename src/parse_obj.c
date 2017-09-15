/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
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

t_vec3	*n_vec3(float x, float y, float z)
{
	t_vec3	*vec;

	vec = (t_vec3 *)sec_malloc(sizeof(t_vec3));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_vec2	*n_vec2(float x, float y)
{
	t_vec2	*vec;

	vec = (t_vec2 *)sec_malloc(sizeof(t_vec2));
	vec->x = x;
	vec->y = y;
	return (vec);
}

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
			ft_atof(LGET(splt, 2))));
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

t_lst	*create_lists(t_app *app)
{
	if (app->vertices != NULL)
		list_destroy_and_free_content(&app->vertices, &free);
	if (app->normals != NULL)
		list_destroy_and_free_content(&app->normals, &free);
	if (app->uvs != NULL)
		list_destroy_and_free_content(&app->uvs, &free);
	app->vertices = list_new();
	app->normals = list_new();
	app->uvs = list_new();
	return (list_new());
}

void	destroy_faces_list(void *content)
{
	t_lst	*face;

	face = (t_lst *)content;
	list_destroy_and_free_content(&face, &free);
}

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

void	try_parse_split(t_lst *splt, t_app *app, t_lst *faces, int line_count)
{
	if (parse_split(splt, app, faces))
	{
		ft_putstr("Failed to parse line ");
		ft_putnbr(line_count);
		ft_putendl(" Exiting...");
		exit(1);
	}
	list_destroy_and_free_content(&splt, &free);
}

void	parse_obj(t_app *app)
{
	char	*line;
	int		fd;
	int		line_count;
	t_lst	*splt;
	t_lst	*faces;

	faces = create_lists(app);
	line = NULL;
	if ((fd = open(app->obj_file, O_RDONLY)) < 0)
	{
		ft_putendl("Unable to open obj file. Exiting...");
		exit(1);
	}
	line_count = 0;
	while (get_next_line(fd, &line) > 0 && ++line_count)
	{
		splt = split(line, ' ');
		free(line);
		try_parse_split(splt, app, faces, line_count);
	}
	app->triangles = triangulate(faces);
	app->vertex_array = arrayfy_triangles_vert(app->triangles);
	app->uv_array = arrayfy_triangles_uv(app->triangles);
	compute_obj_translation(app);
	list_destroy_and_free_content(&faces, &destroy_faces_list);
}
