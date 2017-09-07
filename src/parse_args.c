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

void	parse_arg(t_app *app, int *arg, int argc, char **argv)
{
	if (argv[*arg][1] == 't')
	{
		if (argc > *arg + 1)
		{
			app->tex_file = argv[*arg + 1];
			(*arg)++;
		}
	}
}

void	parse_args(t_app *app, int argc, char **argv)
{
	int		arg;

	arg = 0;
	while ((++arg) < argc)
	{
		if (ft_strlen(argv[arg]) > 1 && argv[arg][0] == '-')
			parse_arg(app, &arg, argc, argv);
		else if (arg == argc - 1)
			app->obj_file = ft_strdup(argv[arg]);
	}
}
