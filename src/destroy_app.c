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

void	destroy_app(t_app *app)
{
	if (app->obj_file != NULL)
		free(app->obj_file);
	app->obj_file = NULL;
	if (app->shader != NULL)
		free(app->shader);
	app->shader = NULL;
	free(app);
}
