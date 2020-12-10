/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:59:46 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/14 14:23:53 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Handles precision per data type.
*/

static char				*handle_precision(t_printf *data, char *res)
{
	if (is_int_specifier(data->c))
		res = handle_number_precision(data, res);
	else if (is_float_specifier(data->c))
		res = handle_number_precision(data, res);
	else if (data->c == 'p')
		return (handle_number_precision(data, res));
	else if (data->c == 's')
		return (handle_string_precision(data, res));
	return (res);
}

/*
** Handles padding based on data->c (variable type from spec)
*/

static char				*handle_padding(t_printf *data, char *res)
{
	if (is_int_specifier(data->c))
		return (handle_int_padding(data, res));
	else if (is_float_specifier(data->c))
		return (handle_float_padding(data, res));
	else if (data->c == 'p')
		return (handle_int_padding(data, res));
	else if (data->c == 's')
		return (handle_string_padding(data, res));
	else if (data->c == 'c')
		return (handle_char_padding(data, res));
	else if (data->c == '%')
		return (handle_string_padding(data, res));
	return (handle_string_padding(data, res));
}

/*
** Sets special case flags for int
*/

static void				handle_int_flag_specials(t_printf *data)
{
	if (data->left_justify ||
		(data->has_precision && data->precision == 0) ||
		data->c == 'b')
		data->pad_zeros = false;
	if (data->c == 'u' || data->c == 'U' ||
		data->c == 'x' || data->c == 'X' ||
		data->c == 'o' || data->c == 'O' || data->c == 'p')
	{
		data->show_sign = false;
		data->is_negative = false;
		data->blank_space = false;
	}
	if (data->show_sign || data->is_negative)
		data->blank_space = false;
}

/*
** Handles formatting per given variable type (specified by data->c)
** and flags.
*/

char					*handle_formatting(t_printf *data, char *res)
{
	if (is_int_specifier(data->c) || data->c == 'p')
		handle_int_flag_specials(data);
	else if (is_float_specifier(data->c))
	{
		if (data->pad_zeros && (data->left_justify ||
			ft_match(res, "*nan") || ft_match(res, "*inf")))
			data->pad_zeros = false;
		if (data->blank_space &&
			(data->show_sign || data->is_negative || ft_match(res, "*nan")))
			data->blank_space = false;
		if (data->show_sign && ft_match(res, "*nan"))
			data->show_sign = false;
	}
	else if (!is_int_specifier(data->c))
	{
		if (data->blank_space || data->left_justify)
			data->pad_zeros = false;
	}
	if (!(res = handle_precision(data, res)))
		return (NULL);
	res = handle_padding(data, res);
	return (res);
}
