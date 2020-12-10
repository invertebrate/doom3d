/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:48:39 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/07 15:43:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_max_double_idx(double *arr, size_t size, size_t *index)
{
	size_t	i;
	double	max;

	i = 0;
	max = arr[i];
	*index = 0;
	while (i < size)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			*index = i;
		}
		i++;
	}
	return (max);
}

int		ft_max_int_idx(int *arr, size_t size, size_t *index)
{
	size_t	i;
	int		max;

	i = 0;
	max = arr[i];
	*index = 0;
	while (i < size)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			*index = i;
		}
		i++;
	}
	return (max);
}

double	ft_min_double_idx(double *arr, size_t size, size_t *index)
{
	size_t	i;
	double	min;

	i = 0;
	min = arr[i];
	*index = 0;
	while (i < size)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			*index = i;
		}
		i++;
	}
	return (min);
}

int		ft_min_int_idx(int *arr, size_t size, size_t *index)
{
	size_t	i;
	int		min;

	i = 0;
	min = arr[i];
	*index = 0;
	while (i < size)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			*index = i;
		}
		i++;
	}
	return (min);
}
