/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_group_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/16 23:16:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void			button_group_set_horizontal(t_button_group *button_group)
{
	button_group->is_horizontal = true;
	button_group_update_position(button_group, button_group->pos);
}

void			button_group_set_space_between(t_button_group *button_group,
					int32_t space_between)
{
	button_group->space_between = space_between;
	button_group_update_position(button_group, button_group->pos);
}

void			button_group_set_selector(t_button_group *button_group,
					int32_t selected_index)
{
	button_group->is_selector = true;
	button_group->selected_index = selected_index;
}

void			button_group_update_position(t_button_group *group,
					t_vec2 pos)
{
	int32_t		i;
	t_vec2		button_pos;
	int32_t		dim_sum[2];

	ml_vector2_copy(pos, group->pos);
	i = -1;
	dim_sum[0] = -group->buttons[0]->width;
	dim_sum[1] = -group->buttons[0]->height;
	while (++i < (int32_t)group->num_buttons)
	{
		if (group->is_horizontal)
		{
			dim_sum[0] += group->buttons[i]->width + group->space_between;
			ml_vector2_add(group->pos, (t_vec2){group->pos[0] +
				dim_sum[0], group->pos[1]}, button_pos);
		}
		else
		{
			dim_sum[1] += group->buttons[i]->height + group->space_between;
			ml_vector2_add(group->pos, (t_vec2){group->pos[0],
				group->pos[1] + dim_sum[1]}, button_pos);
		}
		ml_vector2_copy(button_pos, group->buttons[i]->pos);
	}
}

void			button_group_render(t_button_group *button_group)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)button_group->num_buttons)
		button_render(button_group->buttons[i]);
}
