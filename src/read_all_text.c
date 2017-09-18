/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_all_text.c                                    :+:      :+:    :+:   */
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
	return (length < 0 ? NULL : content);
}
