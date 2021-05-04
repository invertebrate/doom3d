/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 18:21:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 16:41:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks if zero flag (0) is found in between % and specifier
*/

static int	check_zero_flag(t_printf *data,
				int *index, int *found_zero)
{
	int		i;

	i = *index;
	data->pad_zeros = true;
	*found_zero = true;
	if (i - 1 > 0 && data->spec[i - 1] == '.')
	{
		data->pad_zeros = false;
		*found_zero = false;
	}
	while (i < data->spec_len && ft_isdigit(data->spec[i]))
		i++;
	i--;
	*index = i;
	return (true);
}

/*
** Checks if any flag (-+ 0#) is found in between % and specifier
** maps found flags to t_printf data*
*/

int	check_flag(t_printf *data, int *index, int *found_zero)
{
	int		i;

	i = *index;
	if (data->spec[i] == '-')
		data->left_justify = true;
	else if (data->spec[i] == '+')
		data->show_sign = true;
	else if (data->spec[i] == ' ')
		data->blank_space = true;
	else if (data->spec[i] == '0' && !(*found_zero))
		check_zero_flag(data, &i, found_zero);
	else if (ft_isdigit(data->spec[i]))
	{
		while (i < data->spec_len && ft_isdigit(data->spec[i]))
			i++;
		i--;
	}
	else if (data->spec[i] == '#')
		data->zerox = true;
	*index = i;
	return (true);
}

/*
** I do not remember the purpose of this :D (something to do with zerox flag)
*/

int	check_parsed_zero(t_printf *data, char *res)
{
	int				i;
	int				is_zero;

	is_zero = true;
	i = -1;
	while (res[++i])
	{
		if (res[i] != '0')
		{
			is_zero = false;
			break ;
		}
	}
	data->is_zero_res = is_zero;
	return (true);
}

char	get_next_after_percentage(char *fmt, int *i)
{
	while (fmt[*i])
	{
		if (fmt[*i] == '%')
			return (fmt + *i);
		(*i)++;
	}
	return ('\0');
}
