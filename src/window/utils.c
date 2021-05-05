/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 15:15:20 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

/*
** Capture window framerate
*/

uint32_t	window_framerate_capture(uint32_t delta_time)
{
	static uint32_t		delta_time_sum;
	static uint32_t		frames_per_sec;
	static uint32_t		prev_fps;

	delta_time_sum += delta_time;
	frames_per_sec++;
	if (delta_time_sum > 1000.0)
	{
		prev_fps = frames_per_sec;
		delta_time_sum = 0;
		frames_per_sec = 0;
		return (frames_per_sec);
	}
	return (prev_fps);
}

/*
** Draw fps onto window
*/

void	window_fps_draw(t_window *window,
			uint32_t fps, uint64_t delta_time)
{
	char	*fps_str;
	char	*dt_str;

	error_check(!(fps_str = ft_itoa_base_u32(fps, 10)), "Failed to itoa base");
	error_check(!(dt_str = ft_itoa_base_u32(delta_time, 10)),
		"Failed to itoa base");
	window_text_render(window, (t_text_params){
		.text = fps_str, .blend_ratio = 1.0,
		.xy = (int [2]){5, 5},
		.text_color = (SDL_Color){255, 0, 0, 255}},
		window->debug_font);
	window_text_render(window, (t_text_params){
		.text = dt_str, .blend_ratio = 1.0,
		.xy = (int [2]){5, 5 + FONT_SIZE + 5},
		.text_color = (SDL_Color){255, 0, 0, 255}},
		window->debug_font);
	ft_strdel(&fps_str);
	ft_strdel(&dt_str);
}
