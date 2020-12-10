/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 17:29:40 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/31 20:19:15 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Choose eithe sci or positional format. If exponent is >= -4 or < precision
** choose normal, positional format. Else choose scientific format.
** Insignificant (trailing zeros) are stripped unless # flag is used and
** precision is provided.
*/

static char				*choose_g_output(t_printf *data, int *print_lens,
						char *norm_buf, char *sci_buf)
{
	char				*res;
	int					exp;
	int					i;

	i = print_lens[0];
	while (sci_buf[i] != 'e')
		i--;
	exp = ft_atoi(sci_buf + i + 1);
	if (exp >= -4 && exp < data->precision)
	{
		data->var_len = print_lens[1];
		if (!(res = ft_strnew(data->var_len)))
			return (NULL);
		ft_memmove(res, norm_buf, data->var_len);
	}
	else
	{
		data->var_len = print_lens[0];
		if (!(res = ft_strnew(data->var_len)))
			return (NULL);
		ft_memmove(res, sci_buf, data->var_len);
		if (data->c == 'G')
			ft_capitalize(res);
	}
	return (res);
}

/*
** Fill float buffers for both e and F to be chosen later by logic of g_mode
** See above.
*/

static void				get_floats_for_g_mode(t_printf *data,
						char *norm_buf, char *sci_buf, int print_lens[2])
{
	long double			var;

	if (data->type == length_L)
	{
		var = va_arg(data->variables, long double);
		print_lens[0] = ft_dtoa_buf_ld((t_dtoa_params){.precision =
			data->precision, .value_ld = var, .format = FORMAT_SCI,
			.hashtag = data->zerox, .g_mode = true}, sci_buf, DTOA_BUF_SIZE);
		print_lens[1] = ft_dtoa_buf_ld((t_dtoa_params){.precision =
			data->precision, .value_ld = var, .format = FORMAT_NORM,
			.hashtag = data->zerox, .g_mode = true}, norm_buf, DTOA_BUF_SIZE);
	}
	else
	{
		var = va_arg(data->variables, double);
		print_lens[0] = ft_dtoa_buf((t_dtoa_params){.precision =
			data->precision, .value = var, .format = FORMAT_SCI,
			.hashtag = data->zerox, .g_mode = true}, sci_buf, DTOA_BUF_SIZE);
		print_lens[1] = ft_dtoa_buf((t_dtoa_params){.precision =
			data->precision, .value = var, .format = FORMAT_NORM,
			.hashtag = data->zerox, .g_mode = true}, norm_buf, DTOA_BUF_SIZE);
	}
}

/*
** Parses float in either scientific or decimal format. Choosing out of those
** the shorter representation with significant digits.
*/

static char				*parse_g_float(t_printf *data)
{
	char				norm_buf[DTOA_BUF_SIZE];
	char				sci_buf[DTOA_BUF_SIZE];
	int					print_lens[2];

	data->precision = data->precision >= 0 ? data->precision : 6;
	data->precision = data->precision == 0 ? 1 : data->precision;
	get_floats_for_g_mode(data, norm_buf, sci_buf, print_lens);
	data->is_negative = norm_buf[0] == '-';
	return (choose_g_output(data, print_lens, norm_buf, sci_buf));
}

/*
** Parses float in either scientific or decimal format. All floats are
** converted to double, or long double in case of L flag.
** Floats are converted using ft_dtoa, which uses dragon4 algorithm under the
** hood.
*/

static char				*parse_f_float(t_printf *data)
{
	char				*res;
	char				buf[DTOA_BUF_SIZE];

	res = NULL;
	data->precision = data->precision >= 0 ? data->precision : 6;
	if (data->type == length_L)
		data->var_len = ft_dtoa_buf_ld((t_dtoa_params){.precision =
			data->precision, .value_ld = va_arg(data->variables, long double),
			.format = data->c == 'f' || data->c == 'F' ? FORMAT_NORM :
				FORMAT_SCI, .hashtag = data->zerox,
			.g_mode = false}, buf, DTOA_BUF_SIZE);
	else
		data->var_len = ft_dtoa_buf((t_dtoa_params){.precision =
			data->precision, .value = va_arg(data->variables, double),
			.format = data->c == 'f' || data->c == 'F' ? FORMAT_NORM :
			FORMAT_SCI, .hashtag = data->zerox,
			.g_mode = false}, buf, DTOA_BUF_SIZE);
	data->is_negative = buf[0] == '-';
	if (!(res = ft_strnew(data->var_len)))
		return (NULL);
	ft_memmove(res, buf, data->var_len);
	if (data->c == 'E')
		ft_capitalize(res);
	return (res);
}

/*
** Parses float in either scientific or decimal format. Or g mode which
** chooses the shortest format.
*/

char					*parse_float(t_printf *data)
{
	if (data->c == 'f' || data->c == 'F' || data->c == 'e' || data->c == 'E')
		return (parse_f_float(data));
	return (parse_g_float(data));
}
