/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_inf_nan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 13:29:41 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/30 21:30:30 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

uint32_t		format_inf_nan(char *buf, uint64_t mantissa)
{
	uint32_t	print_len;

	print_len = 3;
	if (mantissa == 0)
		ft_memcpy(buf, "inf", print_len);
	else
		ft_memcpy(buf, "nan", print_len);
	buf[print_len] = '\0';
	return (print_len);
}
