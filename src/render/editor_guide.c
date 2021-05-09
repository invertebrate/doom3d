/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_guide.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 20:02:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/08 20:03:49 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	set_guide_text(char *guide)
{
	ft_sprintf(guide, "Switch to next level in level list: Tab\n"
		"Switch to previous level in level list: Ctrl + Tab\n"
		"Move & Strafe: Button W | A | S | D\n"
		"Rotate view: Mouse Middle / Alt + Mouse Move\n"
		"Select Target by mouse: Mouse Left\n"
		"Select Multiple By mouse: Mouse Left + Shift\n"
		"Deselect one: Mouse Right on target\n"
		"Deselect All: Mouse Right on empty\n"
		"Connect to another node: Mouse Right on path node\n"
		"Rotate selected (shift slower): Button R +  X | Y | Z + lshift\n"
		"Move selected on x and z axis, shift slower: Button Arrows + rshift\n"
		"Move selected target on y axis, shift slower: Button O | L\n"
		"Scale selected (with uvs if \\): Button [ | ] + \\\n"
		"Snap selected to Grid: Button Space\n"
		"Toggle selected distance cull mode (environment / npcs): Button C\n"
		"Delete selected: Button Delete\n"
		"Toggle lock vertical movement: Button V\n"
		"Inc/Decrement patrol path node slot: Button =/+ | -\n"
		"Toggle darkness when lights are in scene: Button P\n");
}
