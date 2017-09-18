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

void	parse_file_content(t_app *app, int fd, t_lst *faces)
{
	char	*line;
	int		line_count;
	t_lst	*splt;

	line = NULL;
	line_count = 0;
	while (get_next_line(fd, &line) > 0 && ++line_count)
	{
		splt = split(line, ' ');
		free(line);
		try_parse_split(splt, app, faces, line_count);
	}
}

void	parse_obj(t_app *app)
{
	t_lst	*faces;
	int		fd;

	faces = create_lists(app);
	if ((fd = open(app->obj_file, O_RDONLY)) < 0)
	{
		ft_putendl("Unable to open obj file. Exiting...");
		exit(1);
	}
	parse_file_content(app, fd, faces);
	app->triangles = triangulate(faces);
	compute_missing_uvs(app);
	app->vertex_array = arrayfy_triangles_vert(app->triangles);
	app->uv_array = arrayfy_triangles_uv(app->triangles);
	compute_obj_translation(app);
	list_destroy_and_free_content(&faces, &destroy_faces_list);
}
