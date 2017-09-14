/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void	process_keys(t_app *app)
{
	float toaddx;
	float toaddz;

	toaddx = 0;
	toaddz = 0;
	if (app->keys[123])
		app->camera_rot.y += 0.0005f * 180.f / PI;
	if (app->keys[124])
		app->camera_rot.y -= 0.0005f * 180.f / PI;
	if (app->keys[125])
		app->camera_rot.x -= 0.0005f * 180.f / PI;
	if (app->keys[126])
		app->camera_rot.x += 0.0005f * 180.f / PI;
	if (app->keys[0])
	{
		toaddx += app->camera_speed * cos(app->camera_rot.y);
		toaddz += app->camera_speed * sin(app->camera_rot.y);
	}
	if (app->keys[2])
	{
		toaddx += -app->camera_speed * cos(app->camera_rot.y);
		toaddz += -app->camera_speed * sin(app->camera_rot.y);
	}
	if (app->keys[1])
	{
		toaddx += -app->camera_speed * sin(app->camera_rot.y);
		toaddz += app->camera_speed * cos(app->camera_rot.y);
	}
	if (app->keys[13])
	{
		toaddx += app->camera_speed * sin(app->camera_rot.y);
		toaddz += -app->camera_speed * cos(app->camera_rot.y);
	}
	app->camera_pos.x += toaddx;
	app->camera_pos.z += toaddz;
}

int		loop(void *param)
{
	t_app	*app;
	t_vec3	v;
	t_vec3	r;

	app = (t_app *)param;
	process_keys(app);
	v.x = 0;
	v.y = 0;
	v.z = 5.f;
	app->rot += 0.0001f * 180.f / PI;
	r.x = 0;
	r.y = app->rot;
	r.z = 0;
	app->modelview = mat4_identity();
	app->modelview = mat4_mult(app->modelview, mat4_rotate(mat4_identity(), app->camera_rot));
	app->modelview = mat4_mult(app->modelview, mat4_translate(mat4_identity(), app->camera_pos));
	app->modelview = mat4_mult(app->modelview, mat4_translate(mat4_identity(), v));
	app->modelview = mat4_mult(app->modelview, mat4_rotate(mat4_identity(), r));
	app->modelview = mat4_mult(app->modelview, mat4_translate(mat4_identity(), app->object_trans));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(app->shader->pixel_program);
	glUniformMatrix4fv(glGetUniformLocation(app->shader->pixel_program, "modelview"), 1, GL_TRUE, app->modelview.m);
	glUniformMatrix4fv(glGetUniformLocation(app->shader->pixel_program, "projection"), 1, GL_TRUE, app->projection.m);

	glBindVertexArray(app->vao);
	glDrawArrays(GL_TRIANGLES, 0, app->triangles->size * 3);
	glBindVertexArray(0);

	glUseProgram(0);

	mlx_opengl_swap_buffers(app->win);
	return (1);
}
