/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_temp_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 18:25:34 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/19 22:07:11 by ohakola          ###   ########.fr       */
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

void				l3d_temp_objects_destroy_if_expired(
						t_temp_objects **temp_objects)
{
	t_temp_objects	*curr;
	t_temp_objects	*prev;
	t_temp_objects	*tmp;
	t_temp_object	*temp_obj;

	curr = *temp_objects;
	prev = NULL;
	while (curr)
	{
		temp_obj = curr->content;
		if (temp_obj->lifetime <= 0)
		{
			if (prev)
			{
				prev->next = curr->next;
				tmp = curr;
				curr = curr->next;
				free(tmp);
				tmp = NULL;
			}
			else
			{
				curr = curr->next;
				free(*temp_objects);
				*temp_objects = NULL;
				*temp_objects = curr;
			}
			l3d_destroy_temp_object(temp_obj, 0);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void				l3d_temp_objects_destroy(t_temp_objects **temp_objects)
{
	if (*temp_objects)
	{
		ft_lstdel(temp_objects, l3d_destroy_temp_object);
		*temp_objects = NULL;
	}
}

void				l3d_temp_objects_add(t_temp_objects **temp_objects,
						t_3d_object *object, int32_t lifetime_and_delay[2])
{
	t_temp_object	*tmp_obj;

	error_check(!(tmp_obj = ft_calloc(sizeof(*tmp_obj))),
		"Failed to malloc temp object");
	tmp_obj->obj = object;
	tmp_obj->lifetime = lifetime_and_delay[0];
	tmp_obj->delay = lifetime_and_delay[1];
	tmp_obj->obj->material->shading_opts |=
		e_shading_invisible | e_shading_zero_alpha;
	if (*temp_objects == NULL)
		*temp_objects = ft_lstnew(tmp_obj, sizeof(*tmp_obj));
	else
		ft_lstadd(temp_objects, ft_lstnew(tmp_obj, sizeof(*tmp_obj)));
}

/*
** While delay is left, temp object is invisible. Once delay runs out,
** temp object becomes visible.
*/

void				l3d_temp_objects_update_time(t_temp_objects **temp_objects,
						uint32_t delta_time)
{
	t_temp_objects	*curr;
	t_temp_object	*temp_obj;

	curr = *temp_objects;
	if (!curr)
		return ;
	while (curr)
	{
		temp_obj = curr->content;
		if (temp_obj->delay >= 0)
			temp_obj->delay -= (int32_t)delta_time;
		else
		{
			temp_obj->obj->material->shading_opts =
				(temp_obj->obj->material->shading_opts &
				~e_shading_invisible);
			temp_obj->lifetime -= (int32_t)delta_time;
		}
		curr = curr->next;
	}
}
