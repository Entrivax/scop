/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liblist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBLIST_H
# define LIBLIST_H

# include "libft.h"
# include <stdlib.h>
# define LGET(list, x) list->content[x]
# define LIST_BASE_SIZE 4

typedef struct		s_lst
{
	int				size;
	int				current_allocated_size;
	void			**content;
}					t_lst;

t_lst				*list_new(void);
t_lst				*list_new_with_alloc_size(int size);
int					list_add(t_lst *list, void *content);
void				list_delete_at(t_lst *list, int index);
void				*list_pop_at(t_lst *list, int index);
void				list_clear(t_lst *list);
void				list_free_all(t_lst *list, void (*f)(void *content));
void				list_destroy(t_lst **list);
void				list_destroy_and_free_content(t_lst **list,
								void (*f)(void *content));

#endif
