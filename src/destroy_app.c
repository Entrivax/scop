/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_app.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void	destroy_app_2(t_app *app)
{
	if (app->triangles != NULL)
		list_destroy_and_free_content(&app->triangles, &free);
	if (app->vertices != NULL)
		list_destroy(&app->vertices);
	if (app->normals != NULL)
		list_destroy(&app->normals);
	if (app->uvs != NULL)
		list_destroy(&app->uvs);
}

void	destroy_app(t_app *app)
{
	if (app->obj_file != NULL)
		free(app->obj_file);
	app->obj_file = NULL;
	if (app->tex_file != NULL)
		free(app->tex_file);
	app->tex_file = NULL;
	if (app->tex_data != NULL)
		free(app->tex_data);
	app->tex_data = NULL;
	if (app->vertex_array != NULL)
		free(app->vertex_array);
	app->vertex_array = NULL;
	if (app->uv_array != NULL)
		free(app->uv_array);
	app->uv_array = NULL;
	if (app->shader != NULL)
		free(app->shader);
	app->shader = NULL;
	destroy_app_2(app);
	free(app);
}
