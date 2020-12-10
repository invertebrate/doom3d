/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_mul.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 22:11:51 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/28 14:00:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

static void		perform_mul(t_big_int *small, t_big_int *large,
				t_big_int *res)
{
	uint64_t	carry;
	size_t		s;
	size_t		l;
	size_t		r;
	uint64_t	product;

	s = -1;
	while (++s < small->length)
	{
		if (small->blocks[s] != 0)
		{
			carry = 0;
			l = -1;
			r = s;
			while (++l < large->length)
			{
				product = res->blocks[r] + large->blocks[l] *
					(uint64_t)small->blocks[s] + carry;
				carry = product >> 32;
				res->blocks[r++] = product & 0xFFFFFFFF;
			}
			res->blocks[r] = (uint32_t)(carry & 0xFFFFFFFF);
		}
		r++;
	}
}

/*
** Performs multiplication operation on t_big_int lhs and rhs saving it into
** result.
*/

void			big_int_mul(t_big_int *lhs, t_big_int *rhs, t_big_int *res)
{
	t_big_int	*large;
	t_big_int	*small;
	uint32_t	max_len;
	size_t		i;

	small = lhs->length < rhs->length ? lhs : rhs;
	large = lhs->length < rhs->length ? rhs : lhs;
	max_len = large->length + small->length;
	res->length = max_len;
	i = -1;
	while (++i < max_len)
		res->blocks[i] = 0;
	perform_mul(small, large, res);
	if (max_len > 0 && res->blocks[max_len - 1] == 0)
		res->length = max_len - 1;
}

/*
** Performs multiplication operation on t_big_int lhs and uint32_t saving it
** into result.
*/

void			big_int_mul_u32(t_big_int *lhs, uint32_t rhs, t_big_int *res)
{
	uint32_t	carry;
	uint64_t	product;
	size_t		i;

	carry = 0;
	i = -1;
	res->length = lhs->length;
	while (++i < lhs->length)
	{
		product = (uint64_t)lhs->blocks[i] * rhs + carry;
		res->blocks[i] = (uint32_t)(product & 0xFFFFFFFF);
		carry = product >> 32;
	}
	if (carry != 0)
	{
		res->blocks[i] = (uint32_t)carry;
		res->length = lhs->length + 1;
	}
}

/*
** Doubles a t_big_int saving it into result.
*/

void			big_int_mul_2(t_big_int *lhs, t_big_int *res)
{
	uint32_t	carry;
	uint32_t	cur;
	size_t		i;

	carry = 0;
	i = -1;
	res->length = lhs->length;
	while (++i < lhs->length)
	{
		cur = lhs->blocks[i];
		res->blocks[i] = (cur << 1) | carry;
		carry = cur >> 31;
	}
	if (carry != 0)
	{
		res->blocks[i] = carry;
		res->length = lhs->length + 1;
	}
}
