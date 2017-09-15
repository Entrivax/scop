/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void	swap_bytes(unsigned char *c1, unsigned char *c2)
{
	unsigned char	tmp;

	tmp = *c1;
	*c1 = *c2;
	*c2 = tmp;
}

void	load_tex(t_app *app)
{
	int		fd;
	int		i;

	if ((fd = open(app->tex_file, O_RDONLY)) == -1)
		return ;
	if (read_int(fd, &app->tex_height) <= 0 || read_int(fd, &app->tex_width) <= 0)
		return ;
	app->tex_data = sec_malloc(sizeof(unsigned char) * app->tex_height * app->tex_width * 4);
	i = -1;
	while (++i < app->tex_width * app->tex_height)
	{
		read_int(fd, (int *)&app->tex_data[i * 4]);
		swap_bytes(&app->tex_data[i * 4], &app->tex_data[i * 4 + 2]);
	}
}
