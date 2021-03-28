/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:00:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/28 14:58:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort_utils.h"

static void		radix_sort_work(t_thread_pool *pool,
						t_radix_params *thread_params,
						uint32_t *arrays[4])
{
	size_t			shift;

	shift = 0;
	while (shift < RADIXTOTALBITS)
	{
		histogram(pool, thread_params, shift, arrays);
		prefix_sum(thread_params);
		reorder(pool, thread_params, shift, arrays);
		shift += RADIXBITS;
	}
}

static t_bool	is_valid(void)
{
	return (RADIXTOTALBITS % RADIXBITS == 0);
}

/*
** 1. Pads incoming array to be divisible by EXPECTED_THREADS.
** 2. Sorts the padded array
** 3. Copies the padded array values to original array
** @pool, thread pool created earlier that will do the parallel work for sorting
** @array, array to be sorted
** @size, size of array
** @num_work, how many splits on the sort we'll perform, this should be similar
** to the number of threads on the pool, which in turn should be similar to the
** number of logical threads on your processor
*/

void			radix_sort(t_thread_pool *pool, uint32_t *array, size_t size)
{
	uint32_t		tmp[size + EXPECTED_THREADS];
	t_radix_params	*params;
	size_t			padded_size;
	uint32_t		padded_arr[size + EXPECTED_THREADS];
	uint32_t		*padded_ptr;

	padded_ptr = padded_arr;
	padded_size = pad_array(padded_ptr, array, size);
	if (!is_valid() && ft_dprintf(2, "RADIXTOTALBITS % RADIXBITS != 0\n"))
		return ;
	params = ft_calloc(sizeof(*params) * EXPECTED_THREADS);
	if (!params && ft_dprintf(2, "Radix malloc err\n"))
		return ;
	init_params(params, padded_size, false);
	radix_sort_work(pool, params, (uint32_t*[2]){padded_ptr, tmp});
	copy_array(array, padded_ptr, size);
	free(params);
}

void			radix_sort_key_val(t_thread_pool *pool,
					uint32_t *key_vals[2], size_t size)
{
	uint32_t		key_vals_tmp[2][size + EXPECTED_THREADS];
	t_radix_params	*params;
	size_t			padded_size;
	uint32_t		padded_key_vals[2][size + EXPECTED_THREADS];
	uint32_t		*padded_key_vals_ptr[2];

	padded_key_vals_ptr[0] = padded_key_vals[0];
	padded_key_vals_ptr[1] = padded_key_vals[1];
	padded_size = pad_array_key_val(padded_key_vals_ptr, key_vals, size);
	if (!is_valid() && ft_dprintf(2, "RADIXTOTALBITS % RADIXBITS != 0\n"))
		return ;
	params = ft_calloc(sizeof(*params) * EXPECTED_THREADS);
	if (!params && ft_dprintf(2, "Radix malloc err\n"))
		return ;
	init_params(params, padded_size, true);
	radix_sort_work(pool, params,
		(uint32_t*[4]){padded_key_vals_ptr[0], padded_key_vals_ptr[1],
		key_vals_tmp[0], key_vals_tmp[1]});
	copy_array_key_vals(key_vals, padded_key_vals_ptr, size);
	free(params);
}
