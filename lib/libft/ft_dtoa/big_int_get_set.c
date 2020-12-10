/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_get_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 22:10:19 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 00:51:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

/*
** Sets t_big_int with value uint64_t.
*/

void			big_int_set_u64(t_big_int *b, uint64_t val)
{
	if (val > 0xFFFFFFFF)
	{
		b->blocks[0] = val & 0xFFFFFFFF;
		b->blocks[1] = (val >> 32) & 0xFFFFFFFF;
		b->length = 2;
	}
	else if (val != 0)
	{
		b->blocks[0] = val & 0xFFFFFFFF;
		b->length = 1;
	}
	else
		b->length = 0;
}

/*
** Sets t_big_int with value uint32_t.
*/

void			big_int_set_u32(t_big_int *b, uint32_t val)
{
	if (val != 0)
	{
		b->blocks[0] = val;
		b->length = (val != 0);
	}
	else
		b->length = 0;
}
