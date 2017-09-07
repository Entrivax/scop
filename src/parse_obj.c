/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

char	*str_alloc_cpy(char *src, size_t start, size_t length)
{
	char	*dst;
	size_t	i;

	dst = (char *)sec_malloc(length + 1);
	i = 0;
	while (i < len)
	{
		dst[i] = src[start + i];
		i++;
	}
	return (dst);
}

t_lst	*split(char *str, char sep)
{
	int		start;
	int		i;
	bool	cutting;
	t_lst	*lst;
	char	**split;

	i = -1;
	cutting = false;
	lst = list_new();
	while (str[++i])
	{
		if (!cutting && str[i] == sep)
			continue;
		if (!cutting && str[i] != sep)
		{
			cutting = true;
			start = i;
			continue;
		}
		if (cutting && str[i] == sep)
		{
			cutting = false;
			list_add(lst, str_alloc_cpy(str, start, i - start));
		}
	}
	if (cutting)
		list_add(lst, str_alloc_cpy(str, start, i - start));
	return (lst);
}

t_vec3	*n_vec3(float x, float y, float z)
{
	t_vec3	*vec;
	
	vec = (t_vec3 *)sec_malloc(sizeof(t_vec3));
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

int		parse_face(t_lst *splt, t_lst *vertices, t_lst *faces)
{
	t_face	*face;
	int		i;
	int		v;

	i = 0;
	while (++i < splt->size)
	{
		if (!ft_isnumber(LGET(splt, i)))
			return (1);
	}
	face = list_new();
	i = 0;
	while (++i < splt->size)
	{
		if ((v = ft_atoi(LGET(splt, i)) - 1) < 0 || v > vertices->size)
			return (1);
		list_add(face, LGET(vertices, v));
	}
	list_add(faces, face);
	return (0);
}

int		parse_split(t_lst *splt, t_lst *vertices, t_lst *faces)
{
	if (splt.size == 0)
		list_destroy(&split);
	if (ft_strcmp("v", LGET(splt, 0)))
	{
		if (splt->size != 4 || !ft_isnumber(LGET(splt, 1)) ||
			!ft_isnumber(LGET(splt, 2)) || !ft_isnumber(LGET(splt, 3)))
			return (1);
		list_add(vertices, n_vec3(ft_atof(LGET(splt, 1)),
			ft_atof(LGET(splt, 2)), ft_atof(LGET(splt, 3))));
	}
	else if (ft_strcmp("f", LGET(splt, 0)))
	{
		if (splt->size < 4 || parse_face(splt, vertices, faces))
			return (1);
	}
	list_destroy_and_free_content(&splt, &free);
	return (0);
}

void	parse_obj(t_app *app)
{
	char	*line;
	int		fd;
	int		line_count;
	t_lst	*splt;

	line = NULL;
	if ((fd = open(app->obj_file)) < 0)
	{
		ft_putendl("Unable to open obj file. Exiting...");
		exit(1);
	}
	line_count = 1;
	while (get_next_line(fd, &line) > 0)
	{
		splt = split(line, ' ');
		if (parse_split(splt))
		{
			ft_putstr("Failed to parse line ");
			ft_putnbr(line_count);
			ft_putendl(" Exiting...");
			exit(1);
		}
		line_count++;
	}
}
