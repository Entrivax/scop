/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H

# define BUF_SIZE 1024

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <OpenGL/gl3.h>
# include "libft.h"
# include "liblist.h"
# include "mlx.h"
# include "mlx_opengl.h"

typedef struct		s_shader_prog
{
	GLuint			pixel_vshader;
	GLuint			pixel_fshader;
	GLuint			pixel_program;
}					t_shader_prog;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	char			*obj_file;
	char			*tex_file;
	t_shader_prog	*shader;
	float			*vertices;
	GLuint			vbo;
	GLuint			vao;
}					t_app;

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef t_lst		t_face;

void			parse_args(t_app *app, int argc, char **argv);
t_shader_prog	*build_shader_prog(char *vspath, char *fspath);
void			*sec_malloc(size_t size);
void			start_app(t_app *app);
void			destroy_app(t_app *app);
int				exit_window(void *param);
int				loop(void *param);
void			parse_obj(t_app *app);

#endif
