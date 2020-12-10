/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:50:42 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/31 20:42:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Pads string with zeros or spaces based on flag settings in data.
*/

static void				*pad_string(t_printf *data, char *res, int start)
{
	if (data->left_justify && data->pad_zeros)
		res = add_chars_to_str_end(res, start, data->width, '0');
	else if (data->left_justify && !data->pad_zeros)
		res = add_chars_to_str_end(res, start, data->width, ' ');
	else if (data->pad_zeros)
		res = add_chars_to_str_begin(res, start, data->width, '0');
	else
		res = add_chars_to_str_begin(res, start, data->width, ' ');
	return (res);
}

/*
** Formats extra padding around float based on given width needs.
*/

char					*handle_float_padding(t_printf *data, char *res)
{
	int		len;
	int		add_size;

	if (data->width <= data->var_len)
		return (res);
	len = data->var_len;
	add_size = data->width - len;
	if (!(res = extend_str(res, len, add_size)))
		return (NULL);
	data->var_len = data->width;
	pad_string(data, res, len);
	if (data->pad_zeros)
		swap_sign_after_padding(data, res, add_size);
	return (res);
}

/*
** Formats extra padding around string based on given width needs.
*/

char					*handle_string_padding(t_printf *data, char *res)
{
	int		len;

	len = data->var_len;
	if (data->width <= data->var_len)
		return (res);
	if (!(res = extend_str(res, len, data->width - len)))
		return (NULL);
	data->var_len = data->width;
	pad_string(data, res, len);
	return (res);
}

/*
** Formats extra padding around int based on given width needs.
*/

char					*handle_int_padding(t_printf *data, char *res)
{
	int		len;
	int		add_size;

	if (data->width <= data->var_len)
		return (res);
	len = data->var_len;
	add_size = data->width - len;
	if (!(res = extend_str(res, len, add_size)))
		return (NULL);
	data->var_len = data->width;
	pad_string(data, res, len);
	if (data->pad_zeros)
	{
		swap_zerox(data, res, add_size + 1);
		swap_sign_after_padding(data, res, add_size);
	}
	return (res);
}

/*
** Formats extra padding around char based on given width needs.
*/

char					*handle_char_padding(t_printf *data, char *res)
{
	int		len;

	if (res[0])
		return (handle_string_padding(data, res));
	len = data->var_len;
	if (data->width <= data->var_len)
		return (res);
	if (!(res = extend_str(res, len, data->width - len)))
		return (NULL);
	data->var_len = data->width;
	if (data->left_justify && data->pad_zeros)
		res = add_chars_to_str_end(res, len, data->width, '0');
	else if (data->left_justify && !data->pad_zeros)
		res = add_chars_to_str_end(res, len, data->width, ' ');
	else if (data->pad_zeros)
		res = add_chars_to_null_str_begin(res, len, data->width, '0');
	else
		res = add_chars_to_null_str_begin(res, len, data->width, ' ');
	return (res);
}
