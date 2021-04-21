/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_work.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 21:34:09 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:41:53 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort_utils.h"

void		reorder_work(void *args)
{
	t_radix_params	*params;
	size_t			i;
	size_t			bucket;

	params = args;
	i = -1;
	if (params->is_key_val)
	{
		while (++i < params->bucket_size)
		{
			bucket = (params->arr_keys[i] >> params->shift) & (RADIX - 1);
			params->out_keys[params->index[bucket]] = params->arr_keys[i];
			params->out_vals[params->index[bucket]++] = params->arr_vals[i];
		}
	}
	else
	{
		while (++i < params->bucket_size)
		{
			bucket = (params->arr_keys[i] >> params->shift) & (RADIX - 1);
			params->out_keys[params->index[bucket]++] = params->arr_keys[i];
		}
	}
}

void		histogram_and_local_reorder(void *args)
{
	t_radix_params	*params;
	uint32_t		*arr;
	size_t			i;
	size_t			next_index;

	params = args;
	arr = params->arr_keys;
	i = -1;
	while (++i < HISTOLEN)
		params->count[i] = 0;
	i = -1;
	while (++i < params->bucket_size)
		params->count[(arr[i] >> params->shift) & (RADIX - 1)]++;
	next_index = 0;
	i = -1;
	while (++i < HISTOLEN)
	{
		params->index[i] = next_index;
		next_index += params->count[i];
	}
	reorder_work(params);
}

void		histogram(t_thread_pool *pool,
						t_radix_params *thread_params,
						size_t shift,
						uint32_t *arrays[4])
{
	size_t			i;
	t_radix_params	*param;

	i = -1;
	while (++i < EXPECTED_THREADS)
	{
		param = thread_params + i;
		if (param->is_key_val)
		{
			param->arr_keys = arrays[0] + i * param->bucket_size;
			param->arr_vals = arrays[1] + i * param->bucket_size;
			param->out_keys = arrays[2] + i * param->bucket_size;
			param->out_vals = arrays[3] + i * param->bucket_size;
		}
		else
		{
			param->arr_keys = arrays[0] + i * param->bucket_size;
			param->out_keys = arrays[1] + i * param->bucket_size;
		}
		param->shift = shift;
		thread_pool_add_work(pool, histogram_and_local_reorder, param);
	}
	thread_pool_wait(pool);
}

/*
** Compute prefix
*/

void		prefix_sum(t_radix_params *thread_params)
{
	size_t			i;
	size_t			j;
	size_t			next_index;

	next_index = 0;
	i = -1;
	while (++i < HISTOLEN)
	{
		j = -1;
		while (++j < EXPECTED_THREADS)
		{
			thread_params[j].index[i] = next_index;
			next_index += thread_params[j].count[i];
		}
	}
}

/*
** Reorder array by combining each bucket onto main array
** param->out is now the sortable array.
*/
void		reorder(t_thread_pool *pool,
						t_radix_params *thread_params,
						size_t shift,
						uint32_t *arrays[4])
{
	size_t			i;
	t_radix_params	*param;

	i = -1;
	while (++i < EXPECTED_THREADS)
	{
		param = thread_params + i;
		if (param->is_key_val)
		{
			param->arr_keys = arrays[2] + i * param->bucket_size;
			param->arr_vals = arrays[3] + i * param->bucket_size;
			param->out_keys = arrays[0];
			param->out_vals = arrays[1];
		}
		else
		{
			param->arr_keys = arrays[1] + i * param->bucket_size;
			param->out_keys = arrays[0];
		}
		param->shift = shift;
		thread_pool_add_work(pool, reorder_work, param);
	}
	thread_pool_wait(pool);
}
