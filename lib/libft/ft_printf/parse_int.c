/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 12:52:00 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/14 14:10:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Consumes int variable based on length flags.
*/

static uint64_t			parse_type(t_printf *data)
{
	uint64_t		var;

	if ((data->c == 'U' && (data->c = 'u')) ||
		(data->c == 'D' && (data->c = 'd')) ||
		(data->c == 'O' && (data->c = 'o')))
		data->type = length_ll;
	if (data->type == length_h)
		var = (uint64_t)((short int)va_arg(data->variables, int32_t));
	else if (data->type == length_hh)
		var = (uint64_t)((char)va_arg(data->variables, uint32_t));
	else if (data->type == length_l)
		var = (uint64_t)(va_arg(data->variables, int64_t));
	else if (data->type == length_ll)
		var = (uint64_t)(va_arg(data->variables, int64_t));
	else if (data->type == length_j)
		var = (uint64_t)(va_arg(data->variables, int64_t));
	else if (data->type == length_z)
		var = (uint64_t)(va_arg(data->variables, int64_t));
	else
		var = (uint64_t)va_arg(data->variables, int32_t);
	if ((int64_t)var < 0)
		data->is_negative = true;
	return (var);
}

/*
** Chooses which itoa to use based on length modifiers
*/

static char				*printf_itoa(t_printf *data, uint64_t var,
						int base, int is_signed)
{
	int				is_conversion_up;

	is_conversion_up = data->type == length_l || data->type == length_ll ||
	data->type == length_j || data->type == length_z || data->type == length_t;
	if (!is_signed)
	{
		if (data->type == length_hh)
			return (ft_itoa_base_u32((unsigned char)var, base));
		else if (data->type == length_h)
			return (ft_itoa_base_u32((unsigned short int)var, base));
		else if (is_conversion_up)
			return (ft_itoa_base_u64(var, base));
		else
			return (ft_itoa_base_u32(var, base));
	}
	else if (data->type == length_hh)
		return (ft_itoa_base_32((char)var, base));
	else if (data->type == length_h)
		return (ft_itoa_base_32((short int)var, base));
	else if (is_conversion_up)
		return (ft_itoa_base_64(var, base));
	return (ft_itoa_base_32(var, base));
}

/*
** Parses ints based on int specifiers, and lengths
*/

char					*parse_int(t_printf *data)
{
	char			*res;
	uint64_t		var;

	var = parse_type(data);
	res = NULL;
	if (data->has_precision && data->precision == 0 && var == 0)
		res = ft_strnew(0);
	else if (data->c == 'd' || data->c == 'i')
		res = printf_itoa(data, var, 10, true);
	else if (data->c == 'u' || data->c == 'D')
		res = printf_itoa(data, var, 10, false);
	else if (data->c == 'o' || data->c == 'O')
		res = printf_itoa(data, var, 8, false);
	else if (data->c == 'x' || data->c == 'X')
		res = printf_itoa(data, var, 16, false);
	else if (data->c == 'b')
		res = printf_itoa(data, ft_abs(var), 2, false);
	data->var_len = ft_strlen(res);
	check_parsed_zero(data, res);
	return (res);
}

/*
** Parses address (p, pointer) by outputting hexadecimal value, basically a sub
** case of int
*/

char					*parse_address(t_printf *data)
{
	char			*res;
	uint64_t		var;

	var = va_arg(data->variables, uint64_t);
	if (var != 0)
		res = ft_itoa_base_u64(var, 16);
	else if (var == 0 && ft_abs(data->precision) > 0)
	{
		res = ft_strnew(1);
		res[0] = '0';
	}
	else
		res = ft_strnew(0);
	data->var_len = ft_strlen(res);
	return (res);
}
