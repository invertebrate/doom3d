/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:35:11 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 14:53:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort_utils.h"

void	pad_array(uint32_t *array, size_t size, size_t padded_size)
{
	size_t		i;

	if (size == padded_size)
		return ;
	i = size - 1;
	while (++i < padded_size)
		array[i] = INT32_MAX - 1;
}

void	pad_array_key_val(uint32_t *key_vals[2],
			size_t size, size_t padded_size)
{
	size_t		i;

	if (size == padded_size)
		return ;
	i = size - 1;
	while (++i < padded_size)
	{
		key_vals[0][i] = INT32_MAX - 1;
		key_vals[1][i] = 0;
	}
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
