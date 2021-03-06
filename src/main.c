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

void	init_mlx(t_app *app)
{
	app->width = 1920;
	app->height = 1080;
	app->mlx = mlx_init();
	app->rot = 0;
	app->win = mlx_new_opengl_window(app->mlx, app->width, app->height, "scop");
	mlx_hook(app->win, 17, 0, &exit_window, app);
	mlx_hook(app->win, 2, 0, &key_down, app);
	mlx_hook(app->win, 3, 0, &key_up, app);
	mlx_do_key_autorepeatoff(app->mlx);
	mlx_loop_hook(app->mlx, &loop, app);
	app->camera_speed = 0.06f;
	if (app->tex_data == NULL)
	{
		app->mode = 0;
		app->mode_switch = 0;
	}
}

void	init_gl_2(t_app *app)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, app->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, app->vbo2);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	app->shader = build_shader_prog("./shaders/shader.vs",
		"./shaders/shader.fs");
}

void	init_gl(t_app *app)
{
	ft_putendl((char *)glGetString(GL_RENDERER));
	ft_putendl((char *)glGetString(GL_VERSION));
	app->projection = compute_projection(0.0001f, 100.f, (float)app->width /
		(float)app->height, 70.f);
	if (app->tex_file != NULL)
	{
		glGenTextures(1, &app->texture);
		glBindTexture(GL_TEXTURE_2D, app->texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, app->tex_width,
			app->tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, app->tex_data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, app->tex_filter);
	}
	glGenBuffers(1, &app->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, app->vbo);
	glBufferData(GL_ARRAY_BUFFER, app->triangles->size * 3 * 3 * sizeof(float),
		app->vertex_array, GL_STATIC_DRAW);
	glGenBuffers(1, &app->vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, app->vbo2);
	glBufferData(GL_ARRAY_BUFFER, app->triangles->size * 3 * 2 * sizeof(float),
		app->uv_array, GL_STATIC_DRAW);
	glGenVertexArrays(1, &app->vao);
	glBindVertexArray(app->vao);
	init_gl_2(app);
}

t_app	*create_app(int argc, char **argv)
{
	t_app	*app;

	app = sec_malloc(sizeof(t_app));
	app->tex_filter = GL_LINEAR;
	parse_args(app, argc, argv);
	parse_obj(app);
	load_tex(app);
	init_mlx(app);
	init_gl(app);
	return (app);
}

int		main(int argc, char **argv)
{
	t_app	*app;

	app = create_app(argc, argv);
	start_app(app);
	destroy_app(app);
	app = NULL;
	return (0);
}
