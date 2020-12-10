/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_scientific.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 23:41:48 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/30 21:56:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

/*
** Fraction digits are moved by one to give space for the decimal dot.
*/

static void				move_fraction_digits(t_dragon4_params params,
						uint32_t *fraction_digits, uint32_t *pos)
{
	uint32_t	max_fraction_digits;

	if (!(*fraction_digits > 0 && params.buf_size > 1))
		return ;
	max_fraction_digits = params.buf_size - 2;
	if (*fraction_digits > max_fraction_digits)
		*fraction_digits = max_fraction_digits;
	ft_memmove(params.buf + *pos + 1,
		params.buf + *pos, *fraction_digits);
	params.buf[*pos] = '.';
	*pos += (1 + *fraction_digits);
	params.buf_size -= (1 + *fraction_digits);
}

/*
** After fraction digits, as many zeros as there are remaining after subtracting
** number of fraction digits from precision, are added.
*/

static void				add_trailing_zeros(t_dragon4_params params,
						uint32_t fraction_digits, int32_t precision,
						uint32_t *pos)
{
	uint32_t	zeros;
	uint32_t	zeros_i;

	if (params.buf_size <= 1)
		return ;
	if (fraction_digits == 0)
	{
		if ((precision > (int32_t)fraction_digits &&
			!params.no_trailing_zeros) || params.hashtag)
		{
			params.buf[(*pos)++] = '.';
			params.buf_size--;
		}
	}
	if (precision > (int32_t)fraction_digits && !params.no_trailing_zeros)
	{
		zeros = (precision - fraction_digits);
		if (zeros > params.buf_size - 1)
			zeros = params.buf_size - 1;
		zeros_i = *pos;
		while (zeros_i < *pos + zeros)
			params.buf[zeros_i++] = '0';
		*pos = zeros_i;
	}
}

/*
** Based on the exponent value either + or - is placed after the e in exp buf
** array. tens, hundreds and thousand digits are added in their corresponding
** place. Exp buf is memcopied after the digits.
*/

static void				add_exp_notation(t_dragon4_params params,
						int32_t exp, uint32_t *pos)
{
	char		exp_buf[6];
	uint32_t	exp_size;

	if (params.buf_size <= 1)
		return ;
	exp_buf[0] = 'e';
	if (exp >= 0)
		exp_buf[1] = '+';
	else
	{
		exp_buf[1] = '-';
		exp = -exp;
	}
	set_exp_buf(params, exp, exp_buf, &exp_size);
	ft_memcpy(params.buf + *pos, exp_buf, exp_size);
	*pos += exp_size;
	params.buf_size -= exp_size;
}

/*
** Formats the digit in buffer in scientific format, e.g.:
** 1.123e001
** After first digit, fraction digits are moved onwards and a dot is added.
** Trailing zeros are added.
** Lastly the exponent is placed at the end of buffer.
*/

uint32_t				format_scientific(t_dragon4_params params,
						int32_t precision)
{
	int32_t		exp;
	uint32_t	digits;
	uint32_t	fraction_digits;
	uint32_t	pos;

	exp = 0;
	params.exp = &exp;
	digits = dragon4(params);
	if (params.no_trailing_zeros)
		while (params.buf[digits - 1] == '0' && digits >= 2)
			digits--;
	pos = 0;
	if (params.buf_size > 1)
	{
		pos++;
		params.buf_size -= 1;
	}
	fraction_digits = digits - 1;
	move_fraction_digits(params, &fraction_digits, &pos);
	add_trailing_zeros(params, fraction_digits, precision, &pos);
	add_exp_notation(params, exp, &pos);
	params.buf[pos] = '\0';
	return (pos);
}
