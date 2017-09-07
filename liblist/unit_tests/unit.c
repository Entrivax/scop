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

int		g_test_result_of_doom = 0;
int		g_assert_count = 0;

int		atr(long result, char *assertion, char *test)
{
	g_assert_count++;
	if (!result)
	{
		printf("X\n\n☠  Assertion %d failed: \"%s\"\n\t\tin %s\n\n",
			g_assert_count, assertion, test);
		g_test_result_of_doom = 1;
		return (1);
	}
	else
	{
		printf(".");
	}
	return (0);
}

int		assert(long expected, long result, char *assertion, char *test)
{
	g_assert_count++;
	if (expected != result)
	{
		printf("X\n\n☠  Assertion %d failed: \"%s\" /"
			"Expected %ld but was %ld\n\t\tin %s\n\n",
			g_assert_count, assertion, expected, result, test);
		g_test_result_of_doom = 1;
		return (1);
	}
	else
	{
		printf(".");
	}
	return (0);
}

void	test(void (*f)(void), const char *test_name)
{
	g_test_result_of_doom = 0;
	g_assert_count = 0;
	printf("%s : ", test_name);
	f();
	if (g_test_result_of_doom == 0)
	{
		printf(" ✅  Test succeeded !\n");
	}
	else
	{
		printf("❌  Test failed !\n");
	}
}
