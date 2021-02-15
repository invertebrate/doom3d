/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_vector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/15 22:06:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_tri_vec		*l3d_triangle_vec_with_capacity(uint32_t capacity)
{
	t_tri_vec	*vector;

	error_check(capacity == 0, "Cant create triangle vec with 0 capacity");
	if ((!(vector = ft_calloc(sizeof(t_tri_vec))) ||
		!(vector->triangles = ft_calloc(sizeof(t_triangle*) * capacity))) &&
		ft_dprintf(2, "Failed to malloc triangle vector\n"))
		exit(1);
	vector->size = 0;
	vector->capacity = capacity;
	return (vector);
}

/*
** Creates an empty triangle vector.
*/

t_tri_vec		*l3d_triangle_vec_empty(void)
{
	t_tri_vec	*vector;

	if ((!(vector = ft_calloc(sizeof(t_tri_vec))) ||
		!(vector->triangles = ft_calloc(sizeof(t_triangle*) *
			L3D_TRI_VEC_INITIAL_CAPACITY))) &&
		ft_dprintf(2, "Failed to malloc triangle vector\n"))
		exit(1);
	vector->size = 0;
	vector->capacity = L3D_TRI_VEC_INITIAL_CAPACITY;
	return (vector);
}

/*
** Creates a triangle vector data struct out of a triangle pointer array.
** If num triangles is larger than initial vector capactiy, allocates
** num triangles + initial vector capacity.
*/

t_tri_vec		*l3d_triangle_vec(t_triangle **triangles,
				uint32_t num_triangles)
{
	t_tri_vec	*vector;
	uint32_t	capacity;
	int			i;

	capacity = num_triangles > L3D_TRI_VEC_INITIAL_CAPACITY ?
		num_triangles + L3D_TRI_VEC_INITIAL_CAPACITY :
		L3D_TRI_VEC_INITIAL_CAPACITY;
	if ((!(vector = ft_calloc(sizeof(t_tri_vec))) ||
		!(vector->triangles = ft_calloc(sizeof(t_triangle*) * capacity))) &&
		ft_dprintf(2, "Failed to malloc triangle vector\n"))
		exit(1);
	i = -1;
	while (++i < (int)num_triangles)
		vector->triangles[i] = triangles[i];
	vector->size = num_triangles;
	vector->capacity = capacity;
	return (vector);
}

/*
** Pushes triangle pointer to the triangle vector. If capacity is reached,
** allocates more capacity to the vector.
*/

void			l3d_triangle_vec_push(t_tri_vec *vector, t_triangle *triangle)
{
	t_triangle	*temp[vector->size];
	uint32_t	new_capacity;
	int			i;

	if (vector->size < vector->capacity)
		vector->triangles[vector->size++] = triangle;
	else
	{
		new_capacity = vector->capacity * 2;
		i = -1;
		while (++i < (int)vector->size)
			temp[i] = vector->triangles[i];
		free(vector->triangles);
		if (!(vector->triangles =
			ft_calloc(sizeof(t_triangle*) * new_capacity)) &&
			ft_dprintf(2, "Failed to malloc triangle vector new size\n"))
			exit(1);
		i = -1;
		while (++i < (int)vector->size)
			vector->triangles[i] = temp[i];
		vector->triangles[vector->size++] = triangle;
		vector->capacity = new_capacity;
	}
}

void			l3d_triangle_vec_delete(t_tri_vec *vector)
{
	free(vector->triangles);
	free(vector);
}
