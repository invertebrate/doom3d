/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 18:21:16 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 17:13:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Checks if zero flag (0) is found in between % and specifier
*/

static int		check_zero_flag(t_printf *data,
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

int				check_flag(t_printf *data, int *index, int *found_zero)
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
** Checks for variable size flags and maps them to t_printf *data
*/

int				check_length(t_printf *data, int *index, char s)
{
	int		i;

	i = *index;
	if (i - 1 >= 0 && s == 'h' && data->spec[i - 1] == 'h')
		data->type = data->type > length_hh && data->type != length_h ?
			data->type : length_hh;
	else if (s == 'h')
		data->type = data->type > length_h ? data->type : length_h;
	else if (i - 1 >= 0 && s == 'l' && data->spec[i - 1] == 'l')
		data->type = data->type > length_ll && data->type != length_l ?
			data->type : length_ll;
	else if (s == 'l')
		data->type = data->type > length_l ? data->type : length_l;
	else if (s == 'j')
		data->type = data->type > length_j ? data->type : length_j;
	else if (s == 'z')
		data->type = data->type > length_z ? data->type : length_z;
	else if (s == 't')
		data->type = data->type > length_t ? data->type : length_t;
	else if (s == 'L')
		data->type = data->type > length_L ? data->type : length_L;
	return (true);
}

/*
** I do not remember the purpose of this :D (something to do with zerox flag)
*/

int				check_parsed_zero(t_printf *data, char *res)
{
	int				i;
	int				is_zero;

	is_zero = true;
	i = -1;
	while (res[++i])
		if (res[i] != '0' && !(is_zero = false))
			break ;
	data->is_zero_res = is_zero;
	return (true);
}
