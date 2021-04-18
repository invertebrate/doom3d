/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:11:36 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:01:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "window.h"

# define MAX_SELECTED_OBJECTS 512

/*
** A list of submenus under editor that open popup menus
*/
typedef enum				e_editor_menu_index
{
	editor_menu_none = 0,
	editor_menu_prefabs = 1,
	editor_menu_objects = 2,
	editor_menu_textures = 3,
	editor_menu_normalmaps = 4,
	editor_menu_npcs = 5,
	editor_menu_triggers = 6,
	editor_menu_lights = 7,
	editor_menu_guide = 8,
}							t_editor_menu_index;

/*
** A struct that represents editor state for the purpose of editing the game
** world.
*/
typedef struct 				s_editor
{
	t_bool					is_locked_vertical_movement;
	t_bool					is_placing;
	t_bool					is_saving;
	t_bool					is_saved;
	t_bool					is_moving;
	t_bool					is_rotating;
	t_editor_menu_index		editor_menu_id;
	t_button_menu			*editor_menu;
	int32_t					editor_level;
	char					editor_filename[128];
	char					editor_savename[128];
	char					selected_object_str[128];
	t_3d_object				*selected_objects[MAX_SELECTED_OBJECTS];
	int32_t					num_selected_objects;
	int						patrol_slot;
}							t_editor;

/*
** Params list containing parameters required for the creation of
** popup menus.
*/
typedef struct				s_button_menu_params
{
	const char				**button_names;
	int32_t					num_buttons;
	void					(*on_click)(t_button *, void *);
	TTF_Font				*button_font;
}							t_button_menu_params;

#endif