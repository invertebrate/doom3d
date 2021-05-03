/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:35:11 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 18:13:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort_utils.h"

size_t	pad_array(uint32_t *array_out, uint32_t *array,
			size_t size_in)
{
	size_t		i;
	size_t		new_size;
	size_t		remainder;

	remainder = size_in % EXPECTED_THREADS;
	if (remainder == 0)
		new_size = size_in;
	else
		new_size = size_in + EXPECTED_THREADS - remainder;
	i = -1;
	while (++i < size_in)
		array_out[i] = array[i];
	i = size_in - 1;
	while (++i < new_size)
		array_out[i] = INT32_MAX - 1;
	return (new_size);
}

size_t	pad_array_key_val(uint32_t *key_vals_out[2],
			uint32_t *key_vals[2],
			size_t size_in)
{
	size_t		i;
	size_t		new_size;
	size_t		remainder;

	remainder = size_in % EXPECTED_THREADS;
	if (remainder == 0)
		new_size = size_in;
	else
		new_size = size_in + EXPECTED_THREADS - remainder;
	i = -1;
	while (++i < size_in)
	{
		key_vals_out[0][i] = key_vals[0][i];
		key_vals_out[1][i] = key_vals[1][i];
	}
	i = size_in - 1;
	while (++i < new_size)
	{
		key_vals_out[0][i] = INT32_MAX - 1;
		key_vals_out[1][i] = 0;
	}
	return (new_size);
}

void	copy_array(uint32_t *dst, uint32_t *src,
			size_t arrays_size)
{
	size_t	i;

	i = -1;
	while (++i < arrays_size)
		dst[i] = src[i];
}

void	copy_array_key_vals(uint32_t *dst[2], uint32_t *src[2],
			size_t arrays_size)
{
	size_t	i;

	i = -1;
	while (++i < arrays_size)
	{
		dst[0][i] = src[0][i];
		dst[1][i] = src[1][i];
	}
}

void	init_params(t_radix_params *thread_params, size_t padded_size,
			t_bool is_key_val)
{
	size_t	i;

	i = -1;
	while (++i < EXPECTED_THREADS)
	{
		thread_params[i].bucket_size = padded_size / EXPECTED_THREADS;
		thread_params[i].is_key_val = is_key_val;
	}
}
