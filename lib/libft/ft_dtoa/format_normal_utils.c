/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_normal_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:02:47 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 16:21:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

void	format_zero_and_dot(t_dragon4_params params, uint32_t *pos)
{
	if (params.buf_size > 1)
	{
		params.buf[1] = '.';
		*pos += 1;
	}
	if (params.buf_size > 0)
	{
		params.buf[0] = '0';
		*pos += 1;
	}
}

int32_t	get_negative_trim_to(t_dragon4_params params,
			int32_t precision, int32_t exp)
{
	if (params.hashtag)
		return (precision + exp + 2);
	return (1);
}

int32_t	get_trim_to(int32_t exp, int32_t negative_trim_to)
{
	if (exp >= 0)
		return (exp + 1);
	return (negative_trim_to);
}
