/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_input2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 18:34:02 by veilo             #+#    #+#             */
/*   Updated: 2021/05/08 19:58:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	handle_editor_key_input2(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_p)
			push_custom_event(app, event_editor_flip_lights, NULL, NULL);
		if (event.key.keysym.sym == SDLK_c)
			push_custom_event(app, event_object_set_shading_not_cull,
				NULL, NULL);
	}
}
