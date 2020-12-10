/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_mul_modif.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 22:14:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 00:48:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

/*
** Multiplies inputted t_big_int by 2.
*/

void			big_int_mul_2_modif(t_big_int *mod)
{
	uint32_t	carry;
	uint32_t	cur;
	size_t		i;

	carry = 0;
	i = -1;
	while (++i < mod->length)
	{
		cur = mod->blocks[i];
		mod->blocks[i] = (cur << 1) | carry;
		carry = cur >> 31;
	}
	if (carry != 0)
	{
		mod->blocks[i] = carry;
		mod->length = mod->length + 1;
	}
}

/*
**  Multiplies inputted t_big_int by 10.
*/

void			big_int_mul_10_modif(t_big_int *mod)
{
	uint32_t	carry;
	uint64_t	product;
	size_t		i;

	carry = 0;
	i = -1;
	while (++i < mod->length)
	{
		product = (uint64_t)(mod->blocks[i]) * 10ULL + carry;
		mod->blocks[i] = (uint32_t)(product & 0xFFFFFFFF);
		carry = product >> 32;
	}
	if (carry != 0)
	{
		mod->blocks[i] = carry;
		mod->length = mod->length + 1;
	}
}
