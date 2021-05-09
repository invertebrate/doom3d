/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_scientific_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 21:56:24 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 16:13:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

static int	set_exp_buf_tens(char *exp_buf,
				uint32_t ten, uint32_t one)
{
	exp_buf[2] = (char)('0' + ten);
	exp_buf[3] = (char)('0' + one);
	return (1);
}

static int	set_exp_buf_hundreds(char *exp_buf,
				uint32_t hund, uint32_t ten, uint32_t one)
{
	exp_buf[2] = (char)('0' + hund);
	exp_buf[3] = (char)('0' + ten);
	exp_buf[4] = (char)('0' + one);
	return (1);
}

static uint32_t	get_tens_exp_size(t_dragon4_params params)
{
	if (params.buf_size - 1 > 4)
		return (4);
	return (params.buf_size - 1);
}

static uint32_t	get_hund_exp_size(t_dragon4_params params)
{
	if (params.buf_size - 1 > 5)
		return (5);
	return (params.buf_size - 1);
}

void	set_exp_buf(t_dragon4_params params, int32_t exp,
			char *exp_buf, uint32_t *exp_size)
{
	uint32_t	one;
	uint32_t	ten;
	uint32_t	hund;
	uint32_t	thou;

	thou = (exp / 1000);
	hund = (exp - thou * 1000) / 100;
	ten = (exp - thou * 1000 - hund * 100) / 10;
	one = (exp - thou * 1000 - hund * 100 - ten * 10);
	if (hund == 0 && thou == 0 && set_exp_buf_tens(exp_buf, ten, one))
		*exp_size = get_tens_exp_size(params);
	else if (thou == 0 && set_exp_buf_hundreds(exp_buf, hund, ten, one))
		*exp_size = get_hund_exp_size(params);
	else
	{
		exp_buf[2] = (char)('0' + thou);
		exp_buf[3] = (char)('0' + hund);
		exp_buf[4] = (char)('0' + ten);
		exp_buf[5] = (char)('0' + one);
		if (params.buf_size - 1 > 6)
			*exp_size = 6;
		else
			*exp_size = params.buf_size - 1;
	}
}
