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

char			*read_all_text(int fd)
{
	char	buffer[BUF_SIZE];
	char	*content;
	char	*tmp;
	int		length;
	int		content_length;

	content_length = 0;
	content = NULL;
	while ((length = read(fd, buffer, BUF_SIZE)) > 0)
	{
		tmp = sec_malloc(content_length + length + 1);
		if (content != NULL)
			ft_memcpy(tmp, content, content_length);
		ft_memcpy(tmp + content_length, buffer, length);
		content_length += length;
		if (content != NULL)
			free(content);
		content = tmp;
	}
	if (length < 0 && content != NULL)
		free(content);
	return length < 0 ? NULL : content;
}

void			create_program_and_attach_shaders(t_shader_prog	*shader)
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
	return file_content;
}

t_shader_prog	*build_shader_prog(char *vspath, char *fspath)
{
	t_shader_prog	*shader;
	char			*file_content;

	shader = sec_malloc(sizeof(t_shader_prog));
	file_content = get_file_content(vspath,
		"Unable to open vertex shader file. Exiting...");
	shader->pixel_vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader->pixel_vshader, 1, (const char * const*)&file_content, NULL);
	glCompileShader(shader->pixel_vshader);
	free(file_content);
	file_content = get_file_content(fspath,
		"Unable to open fragment shader file. Exiting...");
	shader->pixel_fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader->pixel_fshader, 1, (const char * const*)&file_content, NULL);
	glCompileShader(shader->pixel_fshader);
	free(file_content);
	create_program_and_attach_shaders(shader);
	return (shader);
}
