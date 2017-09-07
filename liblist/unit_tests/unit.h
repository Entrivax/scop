/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpilotto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 14:54:54 by lpilotto          #+#    #+#             */
/*   Updated: 2017/09/04 15:25:35 by lpilotto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_H
# define UNIT_H

# define AT(r) if (atr((r), "\"" #r "\" to be TRUE", (char*)__func__)) return;
# define AF(r) if (atr(!(r), "\"" #r "\" to be FALSE", (char*)__func__)) return;
# define ASSERT(e,r) if (assert(e, r, #e " == " #r, (char*)__func__)) return;

int		atr(long result, char *assertion, char *test);
int		assert(long expected, long result, char *assertion, char *test);
void	test(void (*f)(void), const char *test_name);

#endif
