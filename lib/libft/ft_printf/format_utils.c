/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:18:22 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/14 14:41:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Adds 0x to res if specified.
*/

void				swap_zerox(t_printf *data, char *res, int x_index)
{
	if ((!(data->zerox && (data->c == 'x' || data->c == 'X')) &&
		data->c != 'p') || data->is_zero_res)
		return ;
	res[x_index] = '0';
	res[1] = data->c == 'x' || data->c == 'p' ? 'x' : 'X';
}

/*
** Handles sign placement for int or floats if padding or width
** has been adjusted
*/

void				swap_sign_after_padding(t_printf *data,
					char *res, int sign_index)
{
	if (!(data->c == 'i' || data->c == 'd' || data->c == 'D' ||
		is_float_specifier(data->c)))
		return ;
	if (!(data->has_precision && data->precision > 0) ||
		is_float_specifier(data->c))
	{
		if (data->show_sign && !data->is_negative &&
			(res[sign_index] = '0'))
			res[0] = '+';
		else if (data->is_negative && (res[sign_index] = '0'))
			res[0] = '-';
		else if (data->blank_space && (res[sign_index] = '0'))
			res[0] = ' ';
	}
}

/*
** Swaps sign to it's place if res has been extended specified by width or
** precision.
*/

void				swap_sign_after_precision(t_printf *data,
					char *res, int sign_index)
{
	if (!(data->c == 'i' || data->c == 'd' || data->c == 'D'))
		return ;
	if (data->show_sign && !data->is_negative &&
		(res[sign_index] = '0'))
		res[0] = '+';
	else if (data->is_negative && (res[sign_index] = '0'))
		res[0] = '-';
}

/*
** Handles blank (sign) space if specified by flags.
*/

char				*handle_blank(t_printf *data, char *res)
{
	if (!(res = extend_str(res, data->var_len, 1)))
		return (NULL);
	add_chars_to_str_begin(res, data->var_len, data->var_len + 1, ' ');
	data->var_len += 1;
	return (res);
}
