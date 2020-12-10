/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sub_specs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:26:32 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/31 20:10:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Parses flags and maps that data to t_printf *data.
*/

static int		parse_flags(t_printf *data)
{
	int		i;
	int		found_zero;

	i = 0;
	found_zero = false;
	while (i < data->spec_len && is_sub_specifier(data->spec[i]))
	{
		check_flag(data, &i, &found_zero);
		i++;
	}
	return (true);
}

/*
** Parses precision and maps that data to t_printf *data.
*/

static int		parse_precision(t_printf *data, char *dot)
{
	unsigned	var;

	data->has_precision = true;
	data->precision = 0;
	if (ft_isdigit(*(dot + 1)))
	{
		data->precision = ft_atoi(dot + 1);
	}
	else if (*(dot + 1) == '*')
	{
		var = va_arg(data->variables, unsigned);
		data->precision = (int)var;
	}
	return (true);
}

/*
** Parses width and maps that data to t_printf *data.
*/

static int		parse_width(t_printf *data, int i)
{
	int			has_width;
	int			var;

	has_width = false;
	while (i >= 0 && is_sub_specifier(data->spec[i]))
	{
		if (ft_isdigit(data->spec[i]) && !has_width)
		{
			while (i >= 0 && ft_isdigit(data->spec[i]))
				i--;
			data->width = ft_atoi(data->spec + i + 1);
			has_width = true;
		}
		if (data->spec[i] == '*')
		{
			var = va_arg(data->variables, int);
			if (var < 0)
				data->left_justify = true;
			data->width = !has_width ? ft_abs(var) : data->width;
			has_width = true;
		}
		i--;
	}
	return (true);
}

/*
** Parses lengths and maps that data to t_printf *data.
*/

static int		parse_lengths(t_printf *data)
{
	int			i;

	i = 0;
	while (i < data->spec_len && is_sub_specifier(data->spec[i]))
	{
		check_length(data, &i, data->spec[i]);
		i++;
	}
	return (true);
}

/*
** Parses flags, width and precision from everything between % and spec char
** in fmt. Maps that data to t_printf *data.
** variables are consumed for * flag.
*/

int				parse_sub_specifiers(t_printf *data)
{
	char		*dot;
	int			diff;
	int			i;

	parse_flags(data);
	i = -1;
	dot = NULL;
	while (++i < data->spec_len)
		if (data->spec[i] == '.' && (dot = data->spec + i))
			break ;
	diff = dot - data->spec;
	if (dot)
	{
		parse_width(data, diff - 1);
		parse_precision(data, dot);
	}
	else
		parse_width(data, data->spec_len - 2);
	parse_lengths(data);
	return (true);
}
