/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_obj_read_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/07 14:29:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

/*
** Our obj file reader expects triangulated data, thus this validator tests
** number of vertices, textures and normals equals max incides read from obj
** data.
*/

t_bool				l3d_is_valid_obj(t_obj *obj)
{
	int				i;
	int				j;
	uint32_t		max_indices[3];

	i = -1;
	ft_memset(max_indices, 0, sizeof(max_indices));
	while (++i < (int)obj->num_triangles)
	{
		j = -1;
		while (++j < 3)
		{
			max_indices[0] =
				max_indices[0] > obj->triangles[i * 9 + j * 3 + 0] ?
				max_indices[0] : obj->triangles[i * 9 + j * 3 + 0];
			max_indices[1] =
				max_indices[1] > obj->triangles[i * 9 + j * 3 + 1] ?
				max_indices[1] : obj->triangles[i * 9 + j * 3 + 1];
			max_indices[2] =
				max_indices[2] > obj->triangles[i * 9 + j * 3 + 2] ?
				max_indices[2] : obj->triangles[i * 9 + j * 3 + 2];
		}
	}
	return (max_indices[0] == obj->num_vertices && max_indices[1] ==
		obj->num_v_text_coords && max_indices[2] == obj->num_v_normals);
}

/*
** Parses a vec 3 line from string ref and scrolls the str
** forward along the way.
*/

void				l3d_read_obj_vec3_line(char **str, t_vec3 res)
{
	char	*tmp;

	tmp = *str;
	while (*tmp &&
		(ft_isdigit(*tmp) || *tmp == ' ' || *tmp == '-' || *tmp == '.'))
		tmp++;
	if (*tmp != '\n')
		error_check(true, "Invalid characters in vec3 data (v)");
	res[0] = ft_atod(*str);
	ft_scroll_over(str, ' ');
	res[1] = ft_atod(*str);
	ft_scroll_over(str, ' ');
	res[2] = ft_atod(*str);
	ft_scroll_over(str, '\n');
}

/*
** Parses a vec 2 line from string ref and scrolls the str
** forward along the way.
*/

void				l3d_read_obj_vec2_line(char **str, t_vec3 res)
{
	char	*tmp;

	tmp = *str;
	while (*tmp &&
		(ft_isdigit(*tmp) || *tmp == ' ' || *tmp == '-' || *tmp == '.'))
		tmp++;
	if (*tmp != '\n')
		error_check(true, "Invalid characters in vec2 data (vn || vt)");
	res[0] = ft_atod(*str);
	ft_scroll_over(str, ' ');
	res[1] = ft_atod(*str);
	ft_scroll_over(str, '\n');
}

/*
** Parses a triangulated face line from string ref and scrolls the str
** forward along the way.
*/

void				l3d_read_obj_triangle_line(char **str,
						uint32_t *triangle)
{
	char	*tmp;
	int		i;

	tmp = *str;
	while (*tmp && (*tmp == '/' || ft_isdigit(*tmp) || *tmp == ' '))
		tmp++;
	if (*tmp != '\n')
		error_check(true, "Invalid characters in triangle data");
	i = -1;
	while (++i < 9)
	{
		*(triangle + i) = ft_atoi(*str);
		if (i == 2 || i == 5)
			ft_scroll_over(str, ' ');
		else if (i < 8)
			ft_scroll_over(str, '/');
	}
	tmp = *str;
	while (ft_isdigit(*tmp))
		tmp++;
	if (*tmp != '\n')
		error_check(true, "Invalid triangle, read_obj expect faces to be "
			"triangles e.g. (1/1/1/ 2/2/2 3/3/3)\n");
	ft_scroll_over(str, '\n');
}
