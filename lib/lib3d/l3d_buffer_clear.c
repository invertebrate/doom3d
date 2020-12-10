/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_buffer_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:41:05 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:41:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void						l3d_buffer_uint32_clear(uint32_t *buffer,
									uint32_t size, uint32_t clear_value)
{
	int32_t		i;

	i = 0;
	while (i < (int32_t)size)
	{
		buffer[i] = clear_value;
		buffer[i + 1] = clear_value;
		buffer[i + 2] = clear_value;
		buffer[i + 3] = clear_value;
		i += 4;
	}
}

void						l3d_buffer_float_clear(float *buffer,
									uint32_t size, float clear_value)
{
	int32_t		i;

	i = 0;
	while (i < (int32_t)size)
	{
		buffer[i] = clear_value;
		buffer[i + 1] = clear_value;
		buffer[i + 2] = clear_value;
		buffer[i + 3] = clear_value;
		i += 4;
	}
}
