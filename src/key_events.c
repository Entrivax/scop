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

int				key_down(int keycode, void *param)
{
	t_app	*app;

	app = (t_app*)param;
	if (keycode >= 300 || keycode < 0)
		return (0);
	app->keys[keycode] = 1;
	return(0);
}

int				key_up(int keycode, void *param)
{
	t_app	*app;

	app = (t_app*)param;
	if (keycode >= 300 || keycode < 0)
		return (0);
	app->keys[keycode] = 0;
	return(0);
}
