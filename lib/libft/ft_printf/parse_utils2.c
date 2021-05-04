/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:40:58 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 11:53:21 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ternary(int check, int true_case, int false_case)
{
	if (check)
		return (true_case);
	return (false_case);
}

/*
** Checks for variable size flags and maps them to t_printf *data
*/

int	check_length(t_printf *data, int *index, char s)
{
	int		i;

	i = *index;
	if (i - 1 >= 0 && s == 'h' && data->spec[i - 1] == 'h')
		data->type = ternary(data->type > length_hh && data->type != length_h,
				data->type, length_hh);
	else if (s == 'h')
		data->type = ternary(data->type > length_h, data->type, length_h);
	else if (i - 1 >= 0 && s == 'l' && data->spec[i - 1] == 'l')
		data->type = ternary(data->type > length_ll && data->type != length_l,
				data->type, length_ll);
	else if (s == 'l')
		data->type = ternary(data->type > length_l, data->type, length_l);
	else if (s == 'j')
		data->type = ternary(data->type > length_j, data->type, length_j);
	else if (s == 'z')
		data->type = ternary(data->type > length_z, data->type, length_z);
	else if (s == 't')
		data->type = ternary(data->type > length_t, data->type, length_t);
	else if (s == 'L')
		data->type = ternary(data->type > length_L, data->type, length_L);
	return (true);
}

int	get_width(t_printf *data, int var, int has_width)
{
	if (has_width)
		return (ft_abs(var));
	return (data->width);
}

char	*print_nothing_case(t_printf *data)
{
	data->var_len = 0;
	va_arg(data->variables, unsigned);
	return (ft_strnew(1));
}

long double	get_double_var(t_printf *data)
{
	long double			var;

	if (data->type == length_L)
		var = va_arg(data->variables, long double);
	else
		var = va_arg(data->variables, double);
	return (var);
}
