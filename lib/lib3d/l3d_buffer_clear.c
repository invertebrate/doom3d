/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_buffer_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:41:05 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:18:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Clear uin32_t buffer with clear value
*/
void						l3d_buffer_uint32_clear(uint32_t *buffer,
									uint32_t size, uint32_t clear_value)
{
	int32_t		i;

	i = 0;
	while (i + 3 < (int32_t)size)
	{
		buffer[i] = clear_value;
		buffer[i + 1] = clear_value;
		buffer[i + 2] = clear_value;
		buffer[i + 3] = clear_value;
		i += 4;
	}
}

/*
** Clear float buffer with clear value (e.g. z buffer)
*/
void						l3d_buffer_float_clear(float *buffer,
									uint32_t size, float clear_value)
{
	int32_t		i;

	i = 0;
	while (i + 3 < (int32_t)size)
	{
		buffer[i] = clear_value;
		buffer[i + 1] = clear_value;
		buffer[i + 2] = clear_value;
		buffer[i + 3] = clear_value;
		i += 4;
	}
}
