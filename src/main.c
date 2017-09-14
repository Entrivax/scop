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
	app->width = 800;
	app->height = 600;
	app->mlx = mlx_init();
	app->rot = 0;
	app->win = mlx_new_opengl_window(app->mlx, app->width, app->height, "scop");
	mlx_hook(app->win, 17, 0, &exit_window, app);
	mlx_hook(app->win, 2, 0, &key_down, app);
	mlx_hook(app->win, 3, 0, &key_up, app);
	mlx_do_key_autorepeatoff(app->mlx);
	mlx_loop_hook(app->mlx, &loop, app);
	app->camera_speed = 0.1f;
}

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

void	init_gl(t_app *app)
{
	app->projection = compute_projection(0.0001f, 10.f, (float)app->width / (float)app->height, 70.f);
	glGenBuffers(1, &app->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, app->vbo);
	glBufferData(GL_ARRAY_BUFFER, app->triangles->size * 3 * 3 * sizeof(float), app->vertex_array, GL_STATIC_DRAW);
	glGenVertexArrays(1, &app->vao);
	glBindVertexArray(app->vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, app->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	ft_putendl((char *)glGetString(GL_RENDERER));
	ft_putendl((char *)glGetString(GL_VERSION));
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	app->shader = build_shader_prog("./shaders/shader.vs", "./shaders/shader.fs");
}

t_app	*create_app(int argc, char **argv)
{
	t_app	*app;

	app = sec_malloc(sizeof(t_app));
	parse_args(app, argc, argv);
	parse_obj(app);
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
