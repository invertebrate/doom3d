/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:00:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 14:53:57 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort_utils.h"

static void	radix_sort_work(t_thread_pool *pool,
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

static void	allocate_temp(uint32_t **arr, size_t padded_size)
{
	error_check(!(*arr = ft_calloc(sizeof(uint32_t)
				* padded_size)), "Radix malloc err");
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

void	radix_sort(t_thread_pool *pool, uint32_t *array,
			size_t size, size_t padded_size)
{
	uint32_t		*tmp;
	t_radix_params	*params;

	error_check(!is_valid(), "RADIXTOTALBITS % RADIXBITS != 0");
	error_check(!(params = ft_calloc(sizeof(*params) * EXPECTED_THREADS)),
		"Radix malloc err");
	allocate_temp(&tmp, padded_size);
	pad_array(array, size, padded_size);
	init_params(params, padded_size, false);
	radix_sort_work(pool, params, (uint32_t *[2]){array, tmp});
	free(params);
	free(tmp);
}

/*
** Same as `radix_sort` but for key values
*/

void	radix_sort_key_val(t_thread_pool *pool,
			uint32_t *key_vals[2], size_t size,
			size_t padded_size)
{
	uint32_t		*key_vals_tmp[2];
	t_radix_params	*params;

	error_check(!is_valid(), "RADIXTOTALBITS % RADIXBITS != 0");
	error_check(!(params = ft_calloc(sizeof(*params) * EXPECTED_THREADS)),
		"Radix malloc err");
	allocate_temp(&key_vals_tmp[0], padded_size);
	allocate_temp(&key_vals_tmp[1], padded_size);
	pad_array_key_val(key_vals, size, padded_size);
	init_params(params, padded_size, true);
	radix_sort_work(pool, params,
		(uint32_t *[4]){key_vals[0], key_vals[1],
		key_vals_tmp[0], key_vals_tmp[1]});
	copy_array_key_vals(key_vals, key_vals, size);
	free(params);
	free(key_vals_tmp[0]);
	free(key_vals_tmp[1]);
}
