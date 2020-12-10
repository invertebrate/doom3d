/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_temp_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:25:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 18:27:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

static void			l3d_destroy_temp_object(void *params, size_t size)
{
	t_temp_object	*temp_obj;

	(void)size;
	temp_obj = params;
	l3d_3d_object_destroy(temp_obj->obj);
	free(temp_obj);
	temp_obj = NULL;
}

static t_bool		l3d_temp_objects_expired(t_temp_objects **temp_objects,
						uint32_t current_time,
						uint32_t diff_limit)
{
	t_bool			all_expired;
	t_temp_objects	*tmp;

	tmp = *temp_objects;
	all_expired = true;
	if (!tmp)
		return (all_expired);
	while (tmp)
	{
		if (current_time - ((t_temp_object*)tmp->content)->creation_time <
			diff_limit)
			all_expired = false;
		tmp = tmp->next;
	}
	return (all_expired);
}

void				l3d_temp_objects_destroy_if_expired(
						t_temp_objects **temp_objects,
						uint32_t current_time,
						uint32_t diff_limit)
{
	if (l3d_temp_objects_expired(temp_objects, current_time, diff_limit))
		l3d_temp_objects_destroy(temp_objects);
}

void				l3d_temp_objects_destroy(t_temp_objects **temp_objects)
{
	ft_lstdel(temp_objects, l3d_destroy_temp_object);
	temp_objects = NULL;
}

void				l3d_temp_objects_add(t_temp_objects **temp_objects,
						t_3d_object *object, uint32_t creation_time)
{
	t_temp_object	*tmp_obj;

	error_check(!(tmp_obj = malloc(sizeof(*tmp_obj))),
		"Failed to malloc temp object");
	tmp_obj->obj = object;
	tmp_obj->creation_time = creation_time;
	if (*temp_objects == NULL)
		*temp_objects = ft_lstnew(tmp_obj, sizeof(*tmp_obj));
	else
		ft_lstadd(temp_objects, ft_lstnew(tmp_obj, sizeof(*tmp_obj)));
}
