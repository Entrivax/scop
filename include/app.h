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
# define PI 3.14159265359f

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <OpenGL/gl3.h>
# include <math.h>
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

typedef struct		s_vec4
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec4;

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct		s_vec2
{
	float			x;
	float			y;
}					t_vec2;

typedef struct		s_mat4
{
	float			m[16];
}					t_mat4;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	char			*obj_file;
	char			*tex_file;
	t_shader_prog	*shader;
	GLuint			vbo;
	GLuint			vbo2;
	GLuint			vao;
	GLuint			texture;
	int				tex_width;
	int				tex_height;
	unsigned char	*tex_data;
	t_lst			*triangles;
	t_vec3			*vertex_array;
	t_vec2			*uv_array;
	t_vec3			object_trans;
	t_vec3			camera_pos;
	t_vec3			camera_rot;
	float			camera_speed;
	t_lst			*vertices;
	t_lst			*normals;
	t_lst			*uvs;
	t_mat4			modelview;
	t_mat4			projection;
	float			rot;
	char			keys[300];
}					t_app;

typedef struct		s_vertex
{
	t_vec3			*v;
	t_vec3			*n;
	t_vec2			*uv;
}					t_vertex;

typedef struct		s_triangle
{
	t_vertex		vertices[3];
}					t_triangle;

void			parse_args(t_app *app, int argc, char **argv);
t_shader_prog	*build_shader_prog(char *vspath, char *fspath);
void			*sec_malloc(size_t size);
void			start_app(t_app *app);
void			destroy_app(t_app *app);
int				exit_window(void *param);
int				key_down(int keycode, void *param);
int				key_up(int keycode, void *param);
int				loop(void *param);
void			parse_obj(t_app *app);
t_mat4			mat4_mult(t_mat4 m1, t_mat4 m2);
t_mat4			mat4_translate(t_mat4 m, t_vec3 v);
t_mat4			mat4_rotate(t_mat4 m, t_vec3 v);
t_mat4			mat4_identity();
void			load_tex(t_app *app);
int				read_int(int fd, int *out);
int				read_short(int fd, short *out);
int				read_byte(int fd, unsigned char *out);

#endif
