/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_shader_prog.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"

void			create_program_and_attach_shaders(t_shader_prog *shader)
{
	shader->pixel_program = glCreateProgram();
	glAttachShader(shader->pixel_program, shader->pixel_fshader);
	glAttachShader(shader->pixel_program, shader->pixel_vshader);
	glLinkProgram(shader->pixel_program);
}

char			*get_file_content(char *filepath, char *error_message)
{
	int				fd;
	char			*file_content;

	fd = open(filepath, O_RDONLY);
	if (fd < 0 || (file_content = read_all_text(fd)) == NULL)
	{
		ft_putendl(error_message);
		exit(1);
	}
	close(fd);
	return (file_content);
}

void			build_vertex_shader(t_shader_prog *shader, char *vspath)
{
	char			*file_content;
	GLint			success;

	success = 0;
	file_content = get_file_content(vspath,
		"Unable to open vertex shader file. Exiting...");
	shader->pixel_vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader->pixel_vshader, 1, (const char *const *)&file_content,
		NULL);
	glCompileShader(shader->pixel_vshader);
	glGetShaderiv(shader->pixel_vshader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		ft_putstr("Failed to build vertex shader");
		exit(1);
	}
	free(file_content);
}

void			build_fragment_shader(t_shader_prog *shader, char *fspath)
{
	char			*file_content;
	GLint			success;

	success = 0;
	file_content = get_file_content(fspath,
		"Unable to open fragment shader file. Exiting...");
	shader->pixel_fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader->pixel_fshader, 1, (const char *const *)&file_content,
		NULL);
	glCompileShader(shader->pixel_fshader);
	glGetShaderiv(shader->pixel_fshader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		ft_putstr("Failed to build fragment shader");
		exit(1);
	}
	free(file_content);
}

t_shader_prog	*build_shader_prog(char *vspath, char *fspath)
{
	t_shader_prog	*shader;

	shader = sec_malloc(sizeof(t_shader_prog));
	build_vertex_shader(shader, vspath);
	build_fragment_shader(shader, fspath);
	create_program_and_attach_shaders(shader);
	return (shader);
}
