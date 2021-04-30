CC = gcc
NAME=doom-nukem
DIR_SRC = ./src
DIR_OBJ = temp
LIBSDL2 = ./lib/SDL2
LIBFT = ./lib/libft
LIB3D = ./lib/lib3d
LIBGMATRIX = ./lib/libgmatrix
LIBFTFLAGS = -L$(LIBFT) -lft
LIB3DFLAGS = -L$(LIB3D) -l3d
LIBGMATRIXFLAGS = -L$(LIBGMATRIX) -lgmatrix
DEBUGFLAG = -g
# Linux and MacOS specific includes & libs
# Linux requires sdl2 installed
UNAME := $(shell uname)
UNAME_ALT := $(shell uname -r)
ifeq ($(UNAME), Linux)
	SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	LIB_MATH = -lm
	LIB_PTHRTEAD = -lpthread
else
	SDL_FLAGS = -rpath $(LIBSDL2) \
					-framework SDL2 -F$(LIBSDL2)/ \
					-framework SDL2_image -F$(LIBSDL2)/ \
					-framework SDL2_ttf -F$(LIBSDL2)/ \
					-framework SDL2_mixer -F$(LIBSDL2)/
	SDL_INCLUDES = -I$(LIBSDL2)/SDL2.framework/Headers \
			-I$(LIBSDL2)/SDL2_image.framework/Headers \
			-I$(LIBSDL2)/SDL2_ttf.framework/Headers \
			-I$(LIBSDL2)/SDL2_mixer.framework/Headers
endif
ifeq ($(UNAME_ALT), 5.9.13-1-MANJARO-ARM)
	LINUX_IGNOREW = -Wno-stringop-overflow -Wno-maybe-uninitialized
endif
LIBS = $(LIB3DFLAGS) $(LIBGMATRIXFLAGS) $(LIBFTFLAGS) $(SDL_FLAGS) $(LIB_MATH) $(LIB_PTHRTEAD)

INCLUDES = -I ./include \
		-I$(LIBFT)/include \
		-I$(LIB3D)/include \
		-I$(LIBGMATRIX)/include \
		$(SDL_INCLUDES)

CFLAGS =-Wall -Wextra -Werror -march=native -O3 -flto $(LINUX_IGNOREW)
SOURCES = main.c \
			doom3d.c \
			settings.c \
			player/player.c \
			player/player_jump.c \
			player/player_shoot.c \
			player/player_reload.c \
			player/player_interact.c \
			player/collision.c \
			player/crouch.c \
			player/movement.c \
			player/player_status.c \
			player/player_vitals_render.c \
			player/player_flashlight.c \
			player/player_init.c \
			projectile/projectile_init.c \
			projectile/projectile_update.c \
			projectile/projectile_collision.c \
			projectile/projectile_data/projectile_data_rpg.c \
			projectile/projectile_data/projectile_data_fireball.c \
			player/player_animations1.c \
			player/player_animations2.c \
			player/player_animations3.c \
			inventory/item_data/item_data_fist.c \
			inventory/item_data/item_data_pistol.c \
			inventory/item_data/item_data_rpg.c \
			inventory/item_data/item_data_shotgun.c \
			inventory/inventory_equip.c \
			inventory/inventory_init.c \
			inventory/inventory_init_items.c \
			inventory/inventory_pickup_weapon.c \
			npc/npc_default.c \
			npc/npc_ranged.c \
			npc/npc_hearing.c \
			npc/npc_elevator.c \
			npc/npc_crate.c \
			npc/npc_execute_behavior.c \
			npc/npc_spawn.c \
			npc/npc_trigger_onhit.c \
			npc/npc_update.c \
			npc/npc_pathfinding.c \
			npc/npc_move_utils.c \
			npc/npc_astar_utils.c \
			npc/npc_astar_utils2.c \
			npc/npc_handle_atk_anim.c \
			npc/npc_line_of_sight.c \
			npc/npc_animation.c \
			npc/npc_anim_utils.c \
			npc/npc_move_to_waypoint.c \
			npc/npc_destroy.c \
			npc/npc_enemy_actions.c \
			trigger/trigger.c \
			trigger/trigger_timer.c \
			trigger/trigger_place.c \
			trigger/trigger_place2.c \
			trigger/trigger_handle.c \
			trigger/trigger_place_start_end.c \
			lights/light.c \
			lights/light2.c \
			lights/light_color.c \
			path/path.c \
			path/path2.c \
			path/patrol_path.c \
			object/object_utils.c \
			object/object_utils2.c \
			object/object_update.c \
			object/game_end.c \
			physics/is_grounded.c \
			physics/forces_update.c \
			physics/physics_obj_utils.c \
			camera.c \
			utils.c \
			performance_counter.c \
			notifications/notifications.c \
			menus/editor3d_menu.c \
			menus/editor3d_menu_button_clicks1.c \
			menus/editor3d_menu_button_clicks2.c \
			menus/editor3d_menu_button_clicks3.c \
			menus/settings_menu.c \
			menus/main_menu.c \
			menus/pause_menu.c \
			menus/menu_utils.c \
			menus/menu_button_utils.c \
			menus/popup_menu_utils.c \
			scene/scene.c \
			scene/scene_menus.c \
			scene/scene_update.c \
			scene/cleanup.c \
			scene/scene_assets.c \
			scene/asset_loading/animations_3d.c \
			scene/asset_loading/models.c \
			scene/asset_loading/normal_maps.c \
			scene/asset_loading/textures.c \
			scene/asset_loading/sprites.c \
			scene/asset_loading/skybox.c \
			scene/asset_loading/npcs.c \
			scene/asset_loading/lights.c \
			scene/asset_loading/triggers.c \
			scene/asset_loading/triggers_drops.c \
			scene/asset_loading/prefabs.c \
			scene/scene_content.c \
			editor/editor_selection.c \
			editor/editor_deselection.c \
			editor/editor_utils.c \
			editor/editor_init.c \
			editor/editor_placement1.c \
			editor/editor_placement2.c \
			editor/editor_placement3.c \
			editor/editor_point_on_target.c \
			editor/editor_object_by_mouse.c \
			editor/editor_duplication.c \
			map/level.c \
			map/save.c \
			map/read.c \
			map/key_read.c \
			map/trigger_read.c \
			map/path_read.c \
			map/path_read_utils.c \
			map/object_read.c \
			map/object_read_utils.c \
			map/filename_keys.c \
			map/write_utils.c \
			render/render.c \
			render/render_parallel.c \
			render/render_parallel_work.c \
			render/render_triangle_utils1.c \
			render/render_triangle_utils2.c \
			render/prepare.c \
			render/prepare_utils1.c \
			render/prepare_utils2.c \
			render/prepare_utils3.c \
			render/rasterize.c \
			render/prepare_clip.c \
			render/player_hud.c \
			render/ui.c \
			render/ui_utils.c \
			render/editor_ui.c \
			render/editor_ui_object_info.c \
			render/debug/debug.c \
			render/debug/debug_line.c \
			render/debug/debug_aabb.c \
			render/notifications1.c \
			render/notifications2.c \
			render/render_triangle_pool.c \
			window/text.c \
			window/text_wrapped.c \
			window/text_surface.c \
			window/window.c \
			window/frame.c \
			window/utils.c \
			window/buttons/button_events.c \
			window/buttons/button_group_events.c \
			window/buttons/button_group_utils.c \
			window/buttons/button_group.c \
			window/buttons/button_utils.c \
			window/buttons/button.c \
			window/buttons/button_popup_menu.c \
			window/buttons/button_popup_menu_utils.c \
			window/buttons/button_popup_menu_events.c \
			events/custom_event_handling/media.c \
			events/custom_event_handling/scene.c \
			events/custom_event_handling/control_flow.c \
			events/custom_event_handling/player/interaction.c \
			events/custom_event_handling/player/movement.c \
			events/custom_event_handling/player/weapons.c \
			events/custom_event_handling/objects/translate.c \
			events/custom_event_handling/objects/rotate.c \
			events/custom_event_handling/objects/objects.c \
			events/custom_event_handling/editor/menu.c \
			events/custom_event_handling/editor/selection.c \
			events/custom_event_handling/editor/placement1.c \
			events/custom_event_handling/editor/placement2.c \
			events/custom_event_handling/editor/movement.c \
			events/custom_event_handling/editor/save.c \
			events/custom_event_handling/editor/textures.c \
			events/custom_event_handling/editor/path.c \
			events/mouse_state.c \
			events/input.c \
			events/custom_events.c \
			events/object_custom_events.c \
			events/player_custom_events.c \
			events/keyboard_state.c \
			events/control_flow.c \
			events/editor/editor_custom_events.c \
			events/editor/editor_custom_event_str.c \
			events/editor/editor_transform.c \
			events/editor/editor_input.c \
			events/editor/editor_input2.c \
			events/editor/editor_keyboard_state.c \
			events/editor/editor_mouse_state.c \
			events/custom_event_handling/editor/editor_shading.c \
			sound/sound.c\
			sound/sound_controls.c\
			sound/sound_init.c\
			sound/sound_music_init.c\
			sound/sound_effect_init.c\
			sound/sound_loop.c\
			sound/sound_mp_controls.c\
			sound/sound_mp_reorder.c\
			animations/animation.c \
			animations/animation_utils.c \
			animations/animation_utils2.c

OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
DEV_OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=_dev.o))

all: $(DIR_OBJ) $(NAME)

$(NAME): $(OBJS)
	@make libs
	@printf "\033[32;1mCompiling app...\n\033[0m"
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)
	@printf "\033[32;1mDone. Run: ./$(NAME)\n\033[0m"

debug: $(OBJS)
	@make libs
	@printf "\033[32;1mCompiling app...\n\033[0m"
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS) $(DEBUGFLAG)
	@printf "\033[32;1mDone. Run: ./$(NAME)\n\033[0m"

libs:
	@printf "\033[32;1mCompiling libs...\n\033[0m"
	make -C $(LIBFT)
	make -C $(LIB3D)
	make -C $(LIBGMATRIX)

$(DIR_OBJ):
	@mkdir -p temp
	@mkdir -p temp/menus
	@mkdir -p temp/map
	@mkdir -p temp/scene
	@mkdir -p temp/scene/asset_loading
	@mkdir -p temp/scene/scene_menus
	@mkdir -p temp/editor
	@mkdir -p temp/window
	@mkdir -p temp/window/buttons
	@mkdir -p temp/render
	@mkdir -p temp/render/debug
	@mkdir -p temp/events
	@mkdir -p temp/events/editor
	@mkdir -p temp/events/custom_event_handling
	@mkdir -p temp/events/custom_event_handling/editor
	@mkdir -p temp/events/custom_event_handling/objects
	@mkdir -p temp/events/custom_event_handling/player
	@mkdir -p temp/lights
	@mkdir -p temp/player
	@mkdir -p temp/animations
	@mkdir -p temp/npc
	@mkdir -p temp/object
	@mkdir -p temp/physics
	@mkdir -p temp/trigger
	@mkdir -p temp/path
	@mkdir -p temp/inventory
	@mkdir -p temp/inventory/item_data
	@mkdir -p temp/projectile
	@mkdir -p temp/projectile/projectile_data
	@mkdir -p temp/sound
	@mkdir -p temp/notifications

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

clean:
	@make -C $(LIBFT) clean
	@make -C $(LIB3D) clean
	@make -C $(LIBGMATRIX) clean
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf $(DIR_OBJ)

fclean: clean
	@make -C $(LIBFT) fclean
	@make -C $(LIB3D) fclean
	@make -C $(LIBGMATRIX) fclean
	@/bin/rm -f $(NAME)

re: fclean all

testrun: #this is only for quicker lib3d debug
	@/bin/rm -f $(OBJS)
	@/bin/rm -rf $(DIR_OBJ)
	make all
	./$(NAME)

norm: norminette $(DIR_SRC) $(LIBFT) $(LIB3D) $(LIBGMATRIX) ./include

.PHONY: all, $(DIR_OBJ), clean, fclean
