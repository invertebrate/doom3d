/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_group_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 20:13:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

/*
** Set space between buttons for button group
*/
void			button_group_set_space_between(t_button_group *button_group,
					int32_t space_between)
{
	button_group->space_between = space_between;
	button_group_update_position(button_group, button_group->pos);
}

/*
** Set whether the button group is a selector and select first index / id
*/
void			button_group_set_selector(t_button_group *button_group,
					int32_t selected_index)
{
	button_group->is_selector = true;
	button_group->selected_index = selected_index;
}

/*
** Update position of a button group
*/
void			button_group_update_position(t_button_group *group,
					t_vec2 pos)
{
	int32_t		i;
	t_vec2		button_pos;

	ml_vector2_copy(pos, group->pos);
	ml_vector2_copy(pos, button_pos);
	i = -1;
	while (++i < (int32_t)group->num_buttons)
	{
		if (group->is_horizontal)
			button_pos[0] = group->pos[0] + i * group->buttons[i]->width +
				group->space_between;
		else
			button_pos[1] = group->pos[1] + i * group->buttons[i]->height +
				group->space_between;
		ml_vector2_copy(button_pos, group->buttons[i]->pos);
	}
}

/*
** Render a button group
*/
void			button_group_render(t_button_group *button_group)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)button_group->num_buttons)
		button_render(button_group->buttons[i]);
}
