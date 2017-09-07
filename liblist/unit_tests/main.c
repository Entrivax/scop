/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblist.h"
#include "unit.h"
#include <stdio.h>
#include <unistd.h>

void	print_hex(unsigned char a)
{
	char	*table;

	table = "0123456789ABCDEF";
	write(0, (table + ((a >> 4) & 15)), 1);
	write(0, (table + (a & 15)), 1);
}

void	print_char(unsigned char a)
{
	if (a < ' ' || a > '~')
		write(0, ".", 1);
	else
		write(0, &a, 1);
}

void	print_mem(const void *addr, size_t size)
{
	size_t	i;
	char	a;

	i = 0;
	while (i < size)
	{
		a = 0;
		while (a < 16 && a + i < size)
		{
			print_hex(*((unsigned char *)addr + i + a));
			if (a > 0 && a % 2 == 1)
				write(0, " ", 1);
			a++;
		}
		while (a < 16)
		{
			write(0, "     ", 5);
			a += 2;
		}
		a = -1;
		while (++a < 16 && a + i < size)
			print_char(*((unsigned char *)addr + i + a));
		write(0, "\n", 1);
		i += 16;
	}
}

void	list_new_should_create_new_list_with_base_size(void)
{
	t_lst	*tmp;

	tmp = list_new();
	ASSERT(LIST_BASE_SIZE, tmp->current_allocated_size);
	ASSERT(0, tmp->size);
	AT(tmp->content != NULL);
	free(tmp->content);
	free(tmp);
}

void	list_new_should_create_new_list_with_asked_size(void)
{
	t_lst	*tmp;

	tmp = list_new_with_alloc_size(20);
	ASSERT(20, tmp->current_allocated_size);
	ASSERT(0, tmp->size);
	AT(tmp->content != NULL);
	free(tmp->content);
	free(tmp);
}

void	list_add_should_add_element_to_list(void)
{
	t_lst	*tmp;
	long	value;
	long	value2;

	value = 64375865;
	value2 = 8975498;
	tmp = list_new_with_alloc_size(2);
	list_add(tmp, (void *)value);
	ASSERT(1, tmp->size);
	ASSERT(value, (int)tmp->content[0]);
	list_add(tmp, (void *)value2);
	ASSERT(2, tmp->size);
	ASSERT(value, (int)tmp->content[0]);
	ASSERT(value2, (int)tmp->content[1]);
	free(tmp->content);
	free(tmp);
}

void	list_add_should_add_element_to_list_and_double_list_size_if_list_doesnt_have_enough_memory(void)
{
	t_lst	*tmp;
	long	value;
	long	value2;
	long	value3;

	value = 54773;
	value2 = 43653;
	value3 = 909675;
	tmp = list_new_with_alloc_size(2);
	list_add(tmp, (void *)value);
	ASSERT(2, tmp->current_allocated_size);
	ASSERT(value, (int)tmp->content[0]);
	list_add(tmp, (void *)value2);
	ASSERT(2, tmp->current_allocated_size);
	ASSERT(2, tmp->size);
	ASSERT(value, (int)tmp->content[0]);
	ASSERT(value2, (int)tmp->content[1]);
	list_add(tmp, (void *)value3);
	ASSERT(4, tmp->current_allocated_size);
	ASSERT(3, tmp->size);
	ASSERT(value, (int)tmp->content[0]);
	ASSERT(value2, (int)tmp->content[1]);
	ASSERT(value3, (int)tmp->content[2]);
	list_add(tmp, (void *)value);
	ASSERT(4, tmp->current_allocated_size);
	ASSERT(4, tmp->size);
	ASSERT(value, (int)tmp->content[0]);
	ASSERT(value2, (int)tmp->content[1]);
	ASSERT(value3, (int)tmp->content[2]);
	ASSERT(value, (int)tmp->content[3]);
	list_add(tmp, (void *)value3);
	ASSERT(8, tmp->current_allocated_size);
	ASSERT(5, tmp->size);
	ASSERT(value, (int)tmp->content[0]);
	ASSERT(value2, (int)tmp->content[1]);
	ASSERT(value3, (int)tmp->content[2]);
	ASSERT(value, (int)tmp->content[3]);
	ASSERT(value3, (int)tmp->content[4]);
	free(tmp->content);
	free(tmp);
}

void	list_delete_at_should_delete_element_at_given_index_and_move_values_after_the_deleted_one(void)
{
	t_lst	*tmp;
	long	value;
	long	value2;
	long	value3;
	int		allocated;

	value = 578669234567;
	value2 = 758963434297;
	value3 = 992679352874;
	tmp = list_new_with_alloc_size(2);
	list_add(tmp, (void *)value);
	ASSERT(1, tmp->size);
	ASSERT(value, (long)tmp->content[0]);
	list_add(tmp, (void *)value2);
	ASSERT(2, tmp->size);
	ASSERT(value, (long)tmp->content[0]);
	ASSERT(value2, (long)tmp->content[1]);
	list_add(tmp, (void *)value3);
	ASSERT(3, tmp->size);
	ASSERT(value, (long)tmp->content[0]);
	ASSERT(value2, (long)tmp->content[1]);
	ASSERT(value3, (long)tmp->content[2]);
	allocated = tmp->current_allocated_size;
	list_delete_at(tmp, 1);
	ASSERT(2, tmp->size);
	ASSERT(value, (long)tmp->content[0]);
	ASSERT(value3, (long)tmp->content[1]);
	ASSERT(0, (long)tmp->content[2]);
	ASSERT(0, (long)tmp->content[3]);
	ASSERT(allocated, tmp->current_allocated_size);
}

void	list_pop_at_should_delete_element_at_given_index_and_move_values_after_the_deleted_one_and_return_the_deleted_value(void)
{
	t_lst	*tmp;
	long	value;
	long	value2;
	long	value3;
	int		allocated;
	long	returned_value;

	value = 547245653767386;
	value2 = 765976586754587;
	value3 = 4567419567868974;
	tmp = list_new_with_alloc_size(2);
	list_add(tmp, (void *)value);
	ASSERT(1, tmp->size);
	ASSERT(value, (long)tmp->content[0]);
	list_add(tmp, (void *)value2);
	ASSERT(2, tmp->size);
	ASSERT(value, (long)tmp->content[0]);
	ASSERT(value2, (long)tmp->content[1]);
	list_add(tmp, (void *)value3);
	ASSERT(3, tmp->size);
	ASSERT(value, (long)tmp->content[0]);
	ASSERT(value2, (long)tmp->content[1]);
	ASSERT(value3, (long)tmp->content[2]);
	allocated = tmp->current_allocated_size;
	returned_value = (long)list_pop_at(tmp, 1);
	ASSERT(value2, returned_value);
	ASSERT(2, tmp->size);
	ASSERT(value, (long)tmp->content[0]);
	ASSERT(value3, (long)tmp->content[1]);
	ASSERT(0, (long)tmp->content[2]);
	ASSERT(0, (long)tmp->content[3]);
	ASSERT(allocated, tmp->current_allocated_size);
}

int		main(void)
{
	test(&list_new_should_create_new_list_with_base_size, "list_new_should_create_new_list_with_base_size");
	test(&list_new_should_create_new_list_with_asked_size, "list_new_should_create_new_list_with_asked_size");
	test(&list_add_should_add_element_to_list, "list_add_should_add_element_to_list");
	test(&list_add_should_add_element_to_list_and_double_list_size_if_list_doesnt_have_enough_memory, "list_add_should_add_element_to_list_and_double_list_size_if_list_doesnt_have_enough_memory");
	test(&list_delete_at_should_delete_element_at_given_index_and_move_values_after_the_deleted_one, "list_delete_at_should_delete_element_at_given_index_and_move_values_after_the_deleted_one");
	test(&list_pop_at_should_delete_element_at_given_index_and_move_values_after_the_deleted_one_and_return_the_deleted_value, "list_pop_at_should_delete_element_at_given_index_and_move_values_after_the_deleted_one_and_return_the_deleted_value");
	return (0);
}
