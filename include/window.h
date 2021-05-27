/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/28 00:24:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "libft.h"
# include "lib3d.h"

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

# define PIXEL_FORMAT SDL_PIXELFORMAT_RGBA8888
# define FONT_SIZE 38
# define CLEAR_COLOR 0x700000FF

/*
**	Frame buffer
*/

# define BYTES_PER_PIXEL 8

/*
** Define text's blend ratio between 0.0 and 1.0, text to render,
** xy position and its color
*/

typedef struct s_text_params
{
	const char				*text;
	SDL_Color				text_color;
	int						*xy;
	float					blend_ratio;
}							t_text_params;

/*
** Information struct for fps and delta time
*/

typedef struct s_info
{
	uint32_t				fps;
	uint64_t				delta_time;
	uint64_t				performance_start;
	uint64_t				performance_end;
}							t_info;

/*
** A wrapper for software rasterizer's framebuffer & window information
*/

typedef struct s_window
{
	SDL_Renderer			*renderer;
	SDL_Texture				*frame;
	t_framebuffer			*framebuffer;
	t_framebuffer			*framebuffer_3d;
	t_vec2					view_3d_pos;
	TTF_Font				*main_font;
	TTF_Font				*small_font;
	TTF_Font				*title_font;
	int32_t					width;
	int32_t					height;
	int32_t					pitch;
	t_bool					resized;
	SDL_Window				*window;
	uint32_t				window_id;
	t_bool					is_hidden;
	t_bool					is_fullscreen;
}							t_window;

/*
** Mouse state
*/

typedef struct s_mouse
{
	int32_t				x;
	int32_t				y;
	uint32_t			state;
}							t_mouse;

/*
** Keyboard state
*/

typedef struct s_keyboard
{
	const uint8_t		*state;
}							t_keyboard;

/*
** UI button
*/

typedef struct s_button		t_button;

struct s_button
{
	uint32_t				id;
	const char				*text;
	t_vec2					pos;
	uint32_t				width;
	uint32_t				height;
	t_surface				*texture;
	t_surface				*texture_down;
	t_bool					is_down;
	t_bool					is_hovered;
	void					(*on_click)(t_button *, void *);
	void					(*on_hover)(t_button *, void *);
	void					*on_click_params;
	void					*on_hover_params;
	t_window				*window;
	t_bool					is_active;
};

/*
** UI Button group
*/

typedef struct s_button_group
{
	t_vec2					pos;
	t_button				**buttons;
	uint32_t				num_buttons;
	uint32_t				space_between;
	t_bool					is_horizontal;
	t_bool					is_selector;
	uint32_t				selected_index;
	t_bool					is_active;
	uint32_t				max_width;
	uint32_t				max_height;
}							t_button_group;

/*
** UI Button menu
*/

typedef struct s_button_menu
{
	t_button_group			*menu;
	t_vec2					pos;
	t_bool					is_open;
	uint32_t				background_color;
	uint32_t				border_color;
	t_surface				background;
	int32_t					border_size;
	int32_t					padding;
}							t_button_menu;

/*
** Window
*/

void						window_destroy(t_window *window);
void						window_create(t_window **window_ref,
								int32_t width, int32_t height);
void						window_frame_recreate(t_window *window);
void						window_3d_framebuffer_recreate(t_window *window,
								int32_t dims[2],
								int32_t pos[2]);
void						draw_window_frame(t_window *window);
void						window_frame_clear(t_window *window,
								uint32_t clear_color);
void						window_resize(t_window *window,
								int32_t width, int32_t height);

/*
** Text
*/

void						window_text_render(t_window *window,
								t_text_params params, TTF_Font *font);
void						window_text_render_wrapped(t_window *window,
								t_text_params params, TTF_Font *font);
void						window_text_render_centered(t_window *window,
								t_text_params params, TTF_Font *font);
void						window_text_render_centered_wrapped(
								t_window *window,
								t_text_params params, TTF_Font *font);
SDL_Surface					*surface_from_font_shaded(t_text_params params,
								TTF_Font *font);
SDL_Surface					*surface_from_font_solid(t_text_params params,
								TTF_Font *font);
void						window_text_render_centered_wrapped_shaded(t_window
								*window, t_text_params params, TTF_Font *font);
void						window_text_render_centered_shaded(t_window
								*window, t_text_params params, TTF_Font *font);
void						window_text_render_shaded(t_window *window,
								t_text_params params, TTF_Font *font);
void						window_text_render_wrapped_shaded(t_window *window,
								t_text_params params, TTF_Font *font);

/*
** Utils
*/

void						window_fps_draw(t_window *window,
								uint32_t fps, uint64_t delta_time);
uint32_t					window_framerate_capture(uint32_t time_since_start);

/*
** Buttons
*/

void						button_group_destroy(t_button_group *button_group);
void						button_group_update_position(
								t_button_group *button_group,
								t_vec2 pos);
t_button_group				*button_group_create(t_button **buttons,
								uint32_t num_buttons, t_bool is_horizontal);
void						button_destroy(t_button *button);
void						button_update_position(t_button *button,
								t_vec2 pos);
void						button_set_handles(t_button *button,
								void (*on_click)(t_button *, void *),
								void (*on_hover)(t_button *, void *));
void						button_set_texture(t_button *button,
								t_surface *texture,
								t_surface *texture_down);
t_button					*button_create(t_window *window, uint32_t id,
								const char *text);
void						button_set_handle_params(t_button *button,
								void *on_click_params,
								void *on_hover_params);
void						button_render(t_button *button);
void						button_group_render(t_button_group *button_group);
void						button_group_set_space_between(
								t_button_group *button_group,
								int32_t space_between);
void						button_group_events_handle(
								t_button_group *button_group,
								t_mouse mouse, SDL_Event event);
void						button_events_handle(t_button *button,
								t_mouse mouse, SDL_Event event);
void						button_group_set_selector(
								t_button_group *button_group,
								int32_t	selected_index);
t_bool						button_is_clicked(t_button *button, t_mouse mouse,
								SDL_Event event);
t_bool						button_is_down(t_button *button, t_mouse mouse,
								SDL_Event event);
t_bool						button_is_hovered(t_button *button, t_mouse mouse,
								SDL_Event event);
void						button_state_handle(t_button *button, t_mouse mouse,
								SDL_Event event);

void						button_popup_menu_destroy(
								t_button_menu *popup_menu);
t_button_menu				*button_popup_menu_create(t_button_group *menu,
								t_vec2 pos, int32_t padding,
								uint32_t bg_and_border_color[2]);
void						button_popup_menu_render(t_window *window,
								t_button_menu *popup_menu);
void						button_popup_menu_events_handle(
								t_button_menu *button_menu,
								t_mouse mouse, SDL_Event event);
void						popup_menu_default_dims(t_vec2 dims);
void						button_popup_menu_clamp_position_to_window(
								t_button_menu *popup_menu, t_mouse *mouse);

#endif
