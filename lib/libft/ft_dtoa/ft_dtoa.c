/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 18:19:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/31 20:54:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

/*
** Sets cutoff modes based on the inputted formats and precision
** If precision is negative, use no cutoff and output as many decimals
** as possible.
** With scientific, cutoff includes the total length of the digit array
** because there is always just one digit ahead of the dot. Precision (cutoff
** num is incremented by one to account for that).
** With normal mode the precision defines the cutoff num.
*/

void			set_cutoffs(t_dragon4_params *dragon, t_dtoa_params dtoa)
{
	if (dtoa.precision < 0)
	{
		dragon->cutoff_mode = CUTOFF_NONE;
		dragon->cutoff_num = 0;
	}
	else
	{
		if (dtoa.format == FORMAT_NORM)
		{
			dragon->cutoff_mode = dtoa.g_mode ? CUTOFF_TOTAL_LENGTH :
				CUTOFF_FRACTION_LENGTH;
			dragon->cutoff_num = dtoa.precision;
		}
		else if (dtoa.format == FORMAT_SCI)
		{
			dragon->cutoff_mode = CUTOFF_TOTAL_LENGTH;
			dragon->cutoff_num = dtoa.precision + 1 - dtoa.g_mode;
		}
	}
}

/*
** Presets dragon4 algorithm related parameters before calling the algorithm.
** Float is dissected into mantissa, sign and exponent.
** See: http://www.ryanjuckett.com/programming/printing-floating-point-numbers/
** part-3/
** Mantissa becomes (2^52 + float mantissa)
** Exponent becomes (exponent - 1023 - 52)
** Sign is 1 when negative, 0 when positive thus buffer length is increased by
** sign bit.
*/

static void		set_dragon4_params(t_dragon4_params *dragon, t_dtoa_params dtoa,
				char *buf, uint32_t buf_size)
{
	t_float_dissector	fd;

	fd.f = dtoa.value;
	dragon->no_trailing_zeros = dtoa.g_mode;
	dragon->hashtag = dtoa.hashtag;
	if (fd.b.exp != 0)
	{
		dragon->buf = buf + fd.b.sign;
		dragon->buf_size = buf_size - fd.b.sign - (dtoa.format == FORMAT_NORM);
		dragon->mantissa = (1ULL << 52) | fd.b.fraction;
		dragon->exponent = fd.b.exp - 1023 - 52;
		dragon->mantissa_high_bit_index = 52;
		dragon->has_unequal_margins = (fd.b.exp != 1) && (fd.b.fraction == 0);
	}
	else
	{
		dragon->buf = buf + fd.b.sign;
		dragon->buf_size = buf_size - fd.b.sign - (dtoa.format == FORMAT_NORM);
		dragon->mantissa = fd.b.fraction;
		dragon->exponent = 1 - 1023 - 52;
		dragon->mantissa_high_bit_index = log_base2_64(fd.b.fraction);
		dragon->has_unequal_margins = false;
	}
	set_cutoffs(dragon, dtoa);
}

/*
** Dtoa returns an allocated double value as a char* in either scientific
** or normal format.
*/

char			*ft_dtoa(t_dtoa_params params)
{
	char				buf[DTOA_BUF_SIZE];
	t_dragon4_params	dragon;
	t_float_dissector	fd;

	fd.f = params.value;
	if (fd.b.sign == 1)
		*buf = '-';
	if (fd.b.exp == 0x7FF)
		format_inf_nan(buf + (fd.b.sign == 1 && fd.b.fraction == 0),
			fd.b.fraction);
	else
	{
		set_dragon4_params(&dragon, params, buf, DTOA_BUF_SIZE);
		if (params.format == FORMAT_SCI)
			format_scientific(dragon, params.precision);
		else
			format_normal(dragon, params.precision -
				(params.g_mode && params.hashtag));
	}
	return (ft_strdup(buf));
}

/*
** ft_dtoa_buf Outputs parsed float in either scientific or normal format
** to given buffer.
*/

int				ft_dtoa_buf(t_dtoa_params params, char *buf, int buf_size)
{
	t_dragon4_params	dragon;
	t_float_dissector	fd;
	uint32_t			inf_nan_sign;

	fd.f = params.value;
	if (fd.b.sign == 1)
		*buf = '-';
	inf_nan_sign = (fd.b.sign == 1 && fd.b.fraction == 0);
	if (fd.b.exp == 0x7FF)
		return (format_inf_nan(buf + inf_nan_sign, fd.b.fraction) +
			inf_nan_sign);
	else
	{
		set_dragon4_params(&dragon, params, buf, buf_size);
		if (params.format == FORMAT_SCI)
			return (format_scientific(dragon, params.precision) + fd.b.sign);
		else
			return (format_normal(dragon, params.precision -
				(params.g_mode && params.hashtag)) + fd.b.sign);
	}
}
