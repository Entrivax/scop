/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

t_vec3	*n_vec3(float x, float y, float z)
{
	t_vec3	*vec;

	vec = (t_vec3 *)sec_malloc(sizeof(t_vec3));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_vec2	*n_vec2(float x, float y)
{
	t_vec2	*vec;

	vec = (t_vec2 *)sec_malloc(sizeof(t_vec2));
	vec->x = x;
	vec->y = y;
	return (vec);
}
