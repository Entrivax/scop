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

void	draw(t_app *app)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(app->shader->pixel_program);
	glUniform1f(glGetUniformLocation(app->shader->pixel_program,
		"mode"), app->mode);
	glUniformMatrix4fv(glGetUniformLocation(app->shader->pixel_program,
		"modelview"), 1, GL_TRUE, app->modelview.m);
	glUniformMatrix4fv(glGetUniformLocation(app->shader->pixel_program,
		"projection"), 1, GL_TRUE, app->projection.m);
	glBindVertexArray(app->vao);
	glDrawArrays(GL_TRIANGLES, 0, app->triangles->size * 3);
	glBindVertexArray(0);
	glUseProgram(0);
	mlx_opengl_swap_buffers(app->win);
}

void	compute_modelview(t_app *app, t_vec3 *v, t_vec3 *r)
{
	app->modelview = mat4_identity();
	app->modelview = mat4_mult(app->modelview, mat4_rotate(mat4_identity(),
		app->camera_rot));
	app->modelview = mat4_mult(app->modelview, mat4_translate(mat4_identity(),
		app->camera_pos));
	app->modelview = mat4_mult(app->modelview, mat4_translate(mat4_identity(),
		*v));
	app->modelview = mat4_mult(app->modelview, mat4_rotate(mat4_identity(),
		*r));
	app->modelview = mat4_mult(app->modelview, mat4_translate(mat4_identity(),
		app->object_trans));
}

int		loop(void *param)
{
	t_app	*app;
	t_vec3	v;
	t_vec3	r;

	app = (t_app *)param;
	process_keys(app);
	if (app->mode_switch)
		app->mode += 0.01f;
	else
		app->mode -= 0.01f;
	app->mode = ft_clamp(app->mode, 0.f, 1.f);
	v.x = 0;
	v.y = 0;
	v.z = 5.f;
	app->rot += 0.0001f * 180.f / PI;
	r.x = 0;
	r.y = app->rot;
	r.z = 0;
	compute_modelview(app, &v, &r);
	draw(app);
	return (1);
}
