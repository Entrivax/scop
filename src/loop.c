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

int		loop(void *param)
{
	t_app	*app;
	t_vec4	v;
	t_vec3	r;

	app = (t_app *)param;
	v.x = 0;
	v.y = 0;
	v.z = 5.f;
	v.w = 1;
	app->rot += 0.0001f * 180.f / PI;
	r.x = 0;
	r.y = app->rot;
	r.z = 0;
	app->modelview = mat4_identity();
	app->modelview = mat4_rotate(app->modelview, r);
	app->modelview = mat4_translate(app->modelview, v);
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
