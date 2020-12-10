/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 22:10:54 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 00:56:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

static size_t	add_until_end_of_small(t_big_int *small, t_big_int *large,
				uint64_t *carry, t_big_int *res)
{
	uint64_t	sum;
	size_t		i;

	i = -1;
	while (++i < small->length)
	{
		sum = *carry + (uint64_t)large->blocks[i] + (uint64_t)small->blocks[i];
		*carry = sum >> 32;
		res->blocks[i] = sum & 0xFFFFFFFF;
	}
	return (i);
}

static size_t	add_until_end_of_large(t_big_int *large,
				uint64_t *carry, t_big_int *res, size_t i)
{
	uint64_t	sum;

	i -= 1;
	while (i++ < large->length)
	{
		sum = *carry + (uint64_t)large->blocks[i];
		*carry = sum >> 32;
		res->blocks[i] = sum & 0xFFFFFFFF;
	}
	return (i);
}

/*
** Adds two t_big_int lhs and rhs together resulting in another t_big_int res.
*/

void			big_int_add(t_big_int *lhs, t_big_int *rhs, t_big_int *res)
{
	t_big_int	*large;
	t_big_int	*small;
	uint64_t	carry;
	size_t		i;

	small = lhs->length < rhs->length ? lhs : rhs;
	large = lhs->length < rhs->length ? rhs : lhs;
	res->length = large->length;
	carry = 0;
	i = 0;
	i = add_until_end_of_small(small, large, &carry, res);
	i = add_until_end_of_large(large, &carry, res, i);
	if (carry != 0)
	{
		res->blocks[i] = 1;
		res->length = large->length + 1;
	}
}
