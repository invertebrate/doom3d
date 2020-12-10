/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_obj_read_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:22:07 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:23:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

static void				l3d_obj_parse_v_or_face(char **str, t_obj *obj)
{
	if (**str == 'v' && *(*str + 1) == ' ')
	{
		*str += 2;
		l3d_read_obj_vec3_line(str, obj->v[obj->num_vertices++]);
	}
	else if (**str == 'v' && *(*str + 1) == 't' && *(*str + 2) == ' ')
	{
		*str += 3;
		l3d_read_obj_vec2_line(str, obj->vt[obj->num_v_text_coords++]);
	}
	else if (**str == 'v' && *(*str + 1) == 'n' && *(*str + 2) == ' ')
	{
		*str += 3;
		l3d_read_obj_vec3_line(str, obj->vn[obj->num_v_normals++]);
	}
	else if (**str == 'f' && *(*str + 1) == ' ')
	{
		*str += 2;
		l3d_read_obj_triangle_line(str,
			obj->triangles + obj->num_triangles * 9);
		obj->num_triangles++;
	}
	else
		(*str)++;
}

/*
** Parses obj data from obj string saving all objects into t_obj_content*
*/

void					l3d_obj_str_parse(char *str, t_obj *obj)
{
	ft_memset(obj, 0, sizeof(*obj));
	l3d_obj_content_allocate(obj);
	while (!(*str == 'v' && *(str + 1) == ' '))
		str++;
	while (*str)
		l3d_obj_parse_v_or_face(&str, obj);
}
