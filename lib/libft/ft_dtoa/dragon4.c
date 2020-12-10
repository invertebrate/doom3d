/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 19:27:50 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 12:09:44 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

/*
** Exit dragon4 if mantissa is zero.
*/

static int32_t		zero_if_zero(t_dragon4_params params)
{
	if (params.mantissa == 0)
	{
		*(params.exp) = 0;
		params.buf[0] = '0';
		return (1);
	}
	return (0);
}

/*
** Initial digit exponent calculation based on algorithm outlined in
** www.ryanjuckett.com/programming/printing-floating-point-numbers/part-2/
*/

static int32_t		get_digit_exponent(t_dragon4_params params)
{
	int32_t		digit_exponent;

	digit_exponent =
		(int32_t)(ft_ceil((double)((int32_t)params.mantissa_high_bit_index +
			params.exponent) * LOG10_2 - 0.69));
	if (params.cutoff_mode == CUTOFF_FRACTION_LENGTH &&
		digit_exponent <= -(int32_t)params.cutoff_num)
		digit_exponent = -(int32_t)params.cutoff_num + 1;
	return (digit_exponent);
}

/*
** Dragon4 implementation using the algorithm laid out by ryanjuckett in
** http://www.ryanjuckett.com/programming/printing-floating-point-numbers/
** Here implemented in C and split into small logical functions.
** 1. Compute initial values for
**  value     = scaled_value / scale
**  margin_low = scaled_margins[0] (low) / scale
** 2. Compute the digit exponent (base 10 exponent: e.g. 1.34*10^digit_exponent)
** 3. Based on digit exponent estimation, adjust scale, scaled_value & margins
** 4. Perform big integer divisions on outputdigit = scaled_value / scale
**    until we hit the cutoff or are far enough away from our margins.
** Basically this is an optimized version of following algorthim:
** ================================
** 1. Compute digit exponent
** digit_exponent = (int)floor( log10(value) ); e.g. 123.45 would compute 2
** 2. Compute initial values for numerator and denominator where
** value = numerator / denominator
** if (exponent > 0)
**  value = (value_numerator = mantissa * 2^exponent) / (value_denominator = 1)
** else
**  value = (value_numerator = mantissa) / (value_denominator = 2^(-exponent))
** 3. Scale numerator or denominator so that first digit is in one's place
** e.g. 123.123 => 1.23123
** if (digit_exponent > 0)
**  value_denominator = value_denominator * 10^digit_exponent
** else
**  value_numerator = value_numerator * 10^digit_exponent
** 4. Compute rest of the digits:
** while (value_numerator > 0.0) // Or cutoff if hit's cutoff  limit
**  digit = value_numerator / value_denominator
**  buffer[num_digits++] = (char)digit + '0'
**  // remainder:
**  value_numerator = value_numerator - digit * value_denominator
**  // scale up so that first digit is in one's place
**  value_numerator = value_numerator * 10
*/

uint32_t			dragon4(t_dragon4_params params)
{
	t_big_int	scale;
	t_big_int	scaled_value;
	t_big_int	scaled_margins[2];
	t_big_int	*margin_ptrs[2];
	int32_t		digit_exponent;

	margin_ptrs[0] = &scaled_margins[0];
	margin_ptrs[1] = &scaled_margins[1];
	if (zero_if_zero(params))
		return (1);
	if (params.has_unequal_margins)
		normalized_initial_state(params, &scale, &scaled_value, margin_ptrs);
	else
		denormalized_initial_state(params, &scale, &scaled_value, margin_ptrs);
	digit_exponent = get_digit_exponent(params);
	scale_values_after_exponent_estimation(&scale, &scaled_value,
		margin_ptrs, &digit_exponent);
	*(params.exp) = digit_exponent - 1;
	prepare_values_for_division(&scale, &scaled_value, margin_ptrs);
	if (params.cutoff_mode == CUTOFF_NONE)
		return (output_without_cutoff(params, &scale, &scaled_value,
			margin_ptrs));
	else
		return (output_with_cutoff(params, &scale, &scaled_value));
}
