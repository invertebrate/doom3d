/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:32:24 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 13:33:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_dtoa_format	get_float_f_format(t_printf *data)
{
	t_dtoa_format		format;

	format = FORMAT_SCI;
	if (data->c == 'f' || data->c == 'F')
		format = FORMAT_NORM;
	return (format);
}
