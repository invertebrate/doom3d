/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dragon4_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 18:57:09 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 12:11:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

/*
** Values are scaled based on the digit exponent estimation.
** "if the digit exponent is smaller than the smallest desired digit for
** fractional cutoff, pull the digit back into legal range at which point we
** will round to the appropriate value."
*/

void			scale_values_after_exponent_estimation(t_big_int *scale,
				t_big_int *scaled_value, t_big_int **scaled_margins,
				int32_t *digit_exponent)
{
	t_big_int	temp;
	t_big_int	pow10;

	if (*digit_exponent > 0)
		big_int_mul_pow_10(scale, *digit_exponent, scale);
	else if (*digit_exponent < 0)
	{
		big_int_pow_10(-*digit_exponent, &pow10);
		big_int_mul(scaled_value, &pow10, &temp);
		big_int_copy(&temp, scaled_value);
		big_int_mul(scaled_margins[0], &pow10, &temp);
		big_int_copy(&temp, scaled_margins[0]);
		if (big_int_cmp(scaled_margins[1], scaled_margins[0]) != 0)
			big_int_mul_2(scaled_margins[0], scaled_margins[1]);
	}
	if (big_int_cmp(scaled_value, scale) >= 0)
		*digit_exponent = *digit_exponent + 1;
	else
	{
		big_int_mul_10_modif(scaled_value);
		big_int_mul_10_modif(scaled_margins[0]);
		if (big_int_cmp(scaled_margins[1], scaled_margins[0]) != 0)
			big_int_mul_2(scaled_margins[0], scaled_margins[1]);
	}
}

/*
** Normalized numbers represent the majority of floating point values.
** This function scales the input values so that later the algorithm can divide
** value = scaled_value / scale in the case of normalized floating point
** values
*/

void			normalized_initial_state(t_dragon4_params params,
				t_big_int *scale, t_big_int *scaled_value,
				t_big_int **scaled_margins)
{
	big_int_set_u64(scaled_value, params.mantissa);
	if (params.exponent > 0)
	{
		big_int_shift_left(params.exponent + 2, scaled_value);
		big_int_set_u32(scale, 4);
		big_int_pow_2(params.exponent, scaled_margins[0]);
		big_int_pow_2(params.exponent + 1, scaled_margins[1]);
	}
	else
	{
		big_int_shift_left(2, scaled_value);
		big_int_pow_2(-params.exponent + 2, scale);
		big_int_set_u32(scaled_margins[0], 1);
		big_int_set_u32(scaled_margins[1], 2);
	}
}

/*
** Denormalized numbers represent a set of floating point values that are
** too small to fit in the normalized range. This function scales the
** input values so that later the algorithm can divide
** value = scaled_value / scale in the case of denormalized floating point
** values
*/

void			denormalized_initial_state(t_dragon4_params params,
				t_big_int *scale, t_big_int *scaled_value,
				t_big_int **scaled_margins)
{
	big_int_set_u64(scaled_value, params.mantissa);
	if (params.exponent > 0)
	{
		big_int_shift_left(params.exponent + 1, scaled_value);
		big_int_set_u32(scale, 2);
		big_int_pow_2(params.exponent, scaled_margins[0]);
	}
	else
	{
		big_int_shift_left(1, scaled_value);
		big_int_pow_2(-params.exponent + 1, scale);
		big_int_set_u32(scaled_margins[0], 1);
	}
	scaled_margins[1] = scaled_margins[0];
}

/*
** Before dividing values, they need to be scaled up so that denominator
** highest block is >= 8 and <= 429496729 (highest number that can be
** multiplied by 10 without overflowing the 32 bit block)
*/

void			prepare_values_for_division(t_big_int *scale,
				t_big_int *scaled_value, t_big_int **scaled_margins)
{
	uint32_t	high_block;
	uint32_t	shift;

	high_block = scale->blocks[scale->length - 1];
	if (high_block < 8 || high_block > 429496729)
	{
		shift = (32 + 27 - log_base2_32(high_block)) % 32;
		big_int_shift_left(shift, scale);
		big_int_shift_left(shift, scaled_value);
		big_int_shift_left(shift, scaled_margins[0]);
		if (big_int_cmp(scaled_margins[1], scaled_margins[0]) != 0)
			big_int_mul_2(scaled_margins[0], scaled_margins[1]);
	}
}
