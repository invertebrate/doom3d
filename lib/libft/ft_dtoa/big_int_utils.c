/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 22:08:52 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 00:42:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

/*
** Prints blocks of big int for inspection.
** (t_big_int){3, {1, 5, 3}} =
** 1 * (2^32 - 1)^0 + 2 * (2^32 - 1)^1 + 3 * (2^32 - 1)^2
*/

void			big_int_retard_print(t_big_int *b)
{
	size_t		i;

	i = -1;
	while (++i < b->length)
	{
		ft_putnbr_unsigned(b->blocks[i]);
		if (i < b->length - 1)
			ft_putstr(", ");
	}
	ft_putstr("\n");
}

/*
** Performs a copy operation on big int.
*/

void			big_int_copy(t_big_int *to_copy, t_big_int *res)
{
	size_t		i;
	uint32_t	length;

	length = to_copy->length;
	i = -1;
	while (++i < length)
		res->blocks[i] = to_copy->blocks[i];
	res->length = length;
}

/*
** Compares big int similarly to ft_strcmp, lhs is larger if result is > 1
** lhs is smaller if result is < 1. Ints are equal if 0.
*/

int32_t			big_int_cmp(t_big_int *lhs, t_big_int *rhs)
{
	int32_t		diff;
	int			i;

	diff = lhs->length - rhs->length;
	if (diff != 0)
		return (diff);
	i = lhs->length;
	while (--i >= 0)
	{
		if (lhs->blocks[i] == rhs->blocks[i])
			continue;
		else if (lhs->blocks[i] > rhs->blocks[i])
			return (1);
		else
			return (-1);
	}
	return (0);
}

/*
** Check if big int is zero -> Its length is zero.
*/

t_bool			big_int_is_zero(t_big_int *b)
{
	return (b->length == 0);
}
