/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_divide.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 22:18:43 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 00:55:53 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

static void		divide_out(t_big_int *dividend, t_big_int *divisor,
				uint32_t quotient, uint32_t length)
{
	uint64_t	borrow;
	uint64_t	carry;
	uint64_t	product;
	uint32_t	i;
	uint64_t	diff;

	borrow = 0;
	carry = 0;
	i = -1;
	while (++i < length)
	{
		product = (uint64_t)divisor->blocks[i] *
			(uint64_t)quotient + carry;
		carry = product >> 32;
		diff = (uint64_t)dividend->blocks[i] -
			(product & 0xFFFFFFFF) - borrow;
		borrow = (diff >> 32) & 1;
		dividend->blocks[i] = diff & 0xFFFFFFFF;
	}
	while (length > 0 && dividend->blocks[length - 1] == 0)
		length--;
	dividend->length = length;
}

static void		divide_remaining(t_big_int *dividend, t_big_int *divisor,
				uint32_t length)
{
	uint64_t	borrow;
	uint64_t	diff;
	uint32_t	i;

	i = -1;
	borrow = 0;
	while (++i < length)
	{
		diff = (uint64_t)dividend->blocks[i] -
			(uint64_t)divisor->blocks[i] - borrow;
		borrow = (diff >> 32) & 1;
		dividend->blocks[i] = diff & 0xFFFFFFFF;
	}
	while (length > 0 && dividend->blocks[length - 1] == 0)
		length--;
	dividend->length = length;
}

/*
** Divides t_big_int nominator with t_big_int denominator. This works
** under the assumption that the result is within the range [0,10] and the input
** numbers have been shifted to satisfy:
** !big_int_is_zero(divisor) && // divisor must not be zero
** divisor->blocks[divisor->length - 1] >= 8 && //enough precision to make
**   an accurate first guess at the quotient
** divisor->blocks[divisor->length - 1] < 0xFFFFFFFF && // to prevent overflow
** dividend->length <= divisor->length
** See the master himself: http://www.ryanjuckett.com/programming/
** printing-floating-point-numbers/part-2/
** The function works as part of the dragon4 implementation and results in
** the output digit.
*/

uint32_t		big_int_divide_to_output_digit(t_big_int *dividend,
				t_big_int *divisor)
{
	uint32_t	length;
	uint32_t	quotient;

	if (!big_int_is_zero(divisor) &&
		divisor->blocks[divisor->length - 1] >= 8 &&
		divisor->blocks[divisor->length - 1] < 0xFFFFFFFF &&
		dividend->length <= divisor->length)
	{
		length = divisor->length;
		if (dividend->length < divisor->length)
			return (0);
		quotient = dividend->blocks[length - 1] /
			divisor->blocks[length - 1];
		if (!(quotient <= 9))
			return (0xFFFFFFFF);
		if (quotient != 0)
			divide_out(dividend, divisor, quotient, length);
		if (big_int_cmp(dividend, divisor) >= 0)
		{
			divide_remaining(dividend, divisor, length);
			quotient++;
		}
		return (quotient);
	}
	return (0xFFFFFFFF);
}
