/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

int		key_down(int keycode, void *param)
{
	t_app	*app;

	app = (t_app*)param;
	if (keycode >= 300 || keycode < 0)
		return (0);
	app->keys[keycode] = 1;
	on_key_down(keycode, app);
	return (0);
}

int		key_up(int keycode, void *param)
{
	t_app	*app;

	app = (t_app*)param;
	if (keycode >= 300 || keycode < 0)
		return (0);
	app->keys[keycode] = 0;
	return (0);
}

void	process_keys_2(t_app *app, float *toaddx, float *toaddy, float *toaddz)
{
	if (app->keys[2])
	{
		(*toaddx) += -app->camera_speed * cos(app->camera_rot.y);
		(*toaddz) += -app->camera_speed * sin(app->camera_rot.y);
	}
	if (app->keys[1])
	{
		(*toaddx) += -app->camera_speed * sin(app->camera_rot.y) *
			cos(app->camera_rot.x);
		(*toaddy) += app->camera_speed * sin(app->camera_rot.x);
		(*toaddz) += app->camera_speed * cos(app->camera_rot.y) *
			cos(app->camera_rot.x);
	}
	if (app->keys[13])
	{
		(*toaddx) += app->camera_speed * sin(app->camera_rot.y) *
			cos(app->camera_rot.x);
		(*toaddy) += -app->camera_speed * sin(app->camera_rot.x);
		(*toaddz) += -app->camera_speed * cos(app->camera_rot.y) *
			cos(app->camera_rot.x);
	}
	app->camera_pos.x += *toaddx;
	app->camera_pos.y += *toaddy;
	app->camera_pos.z += *toaddz;
}

void	process_keys(t_app *app)
{
	float toaddx;
	float toaddy;
	float toaddz;

	toaddx = 0;
	toaddy = 0;
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
	process_keys_2(app, &toaddx, &toaddy, &toaddz);
}

void	on_key_down(int keycode, t_app *app)
{
	if (keycode == 17 && app->tex_data != NULL)
		app->mode_switch = !app->mode_switch;
	if (keycode == 53)
		exit_window((void*)app);
}
