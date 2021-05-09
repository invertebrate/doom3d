/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_custom_event_str.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:37:18 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 14:39:02 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	editor_event_to_str_sub1(char *str, t_doom3d_event code)
{
	if (code == event_editor_start_placement)
		ft_sprintf(str, "event_editor_start_placement");
	else if (code == event_editor_end_placement)
		ft_sprintf(str, "event_editor_end_placement");
	else if (code == event_editor_cancel_placement)
		ft_sprintf(str, "event_editor_cancel_placement");
	else if (code == event_editor_start_save)
		ft_sprintf(str, "event_editor_start_save");
	else if (code == event_editor_end_save)
		ft_sprintf(str, "event_editor_end_save");
	else if (code == event_editor_save_type)
		ft_sprintf(str, "event_editor_save_type");
	else if (code == event_editor_save_type_backspace)
		ft_sprintf(str, "event_editor_save_type_backspace");
}

static void	editor_event_to_str_sub2(char *str, t_doom3d_event code)
{
	if (code == event_editor_exit)
		ft_sprintf(str, "event_editor_exit");
	else if (code == event_editor_snap_to_grid)
		ft_sprintf(str, "event_editor_snap_to_grid");
	else if (code == event_editor_move_view_forward)
		ft_sprintf(str, "event_editor_move_view_forward");
	else if (code == event_editor_move_view_sideways)
		ft_sprintf(str, "event_editor_move_view_sideways");
	else if (code == event_editor_rotate_view)
		ft_sprintf(str, "event_editor_rotate_view");
	else if (code == event_editor_toggle_lock_vertical)
		ft_sprintf(str, "event_editor_toggle_lock_vertical");
	else if (code == event_editor_zoom)
		ft_sprintf(str, "event_editor_zoom");
	else if (code == event_editor_flip_lights)
		ft_sprintf(str, "event_editor_flip_lights");
}

void	editor_custom_event_to_str(char *str, t_doom3d_event code)
{
	editor_event_to_str_sub1(str, code);
	editor_event_to_str_sub2(str, code);
	if (code == event_editor_add_texture)
		ft_sprintf(str, "event_editor_add_texture");
	else if (code == event_editor_add_normal_map)
		ft_sprintf(str, "event_editor_add_normal_map");
	else if (code == event_editor_delete)
		ft_sprintf(str, "event_editor_delete");
	else if (code == event_editor_select)
		ft_sprintf(str, "event_editor_select");
	else if (code == event_editor_deselect)
		ft_sprintf(str, "event_editor_deselect");
	else if (code == event_editor_level_switch)
		ft_sprintf(str, "event_editor_level_switch");
	else if (code == event_editor_open_popup_menu)
		ft_sprintf(str, "event_editor_open_popup_menu");
	else if (code == event_editor_increment_patrol_slot)
		ft_sprintf(str, "event_editor_increment_patrol_slot");
	else if (code == event_editor_decrement_patrol_slot)
		ft_sprintf(str, "event_editor_decrement_patrol_slot");
	else if (code == event_editor_in_placement_move)
		ft_sprintf(str, "event_editor_in_placement_move");
	else if (code == event_editor_duplicate)
		ft_sprintf(str, "event_editor_duplicate");
}
