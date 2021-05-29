CC = gcc
NAME=doom-nukem
DIR_SRC = ./src
DIR_OBJ = temp
LIBFT = ./lib/libft
LIB3D = ./lib/lib3d
LIBGMATRIX = ./lib/libgmatrix
LIBFTFLAGS = -L$(LIBFT) -lft
LIB3DFLAGS = -L$(LIB3D) -l3d
LIBGMATRIXFLAGS = -L$(LIBGMATRIX) -lgmatrix
DEBUGFLAG = -g

# Linux and MacOS specific includes & libs & library check files
RUN_INSTALL_SCRIPT = no
# ====================
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	LIB_MATH = -lm
	LIB_PTHRTEAD = -lpthread
	LIBSDL2FILE = /usr/lib/x86_64-linux-gnu/libSDL2.a
	LIBSDL2IMAGEFILE = /usr/lib/x86_64-linux-gnu/libSDL2_image.a
	LIBSDL2TTFFILE = /usr/lib/x86_64-linux-gnu/libSDL2_ttf.a
	LIBSDL2MIXERFILE = /usr/lib/x86_64-linux-gnu/libSDL2_mixer.a
else ifeq ($(UNAME), Darwin)
	SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
	LIBSDL2FILE = /usr/local/lib/libSDL2.a
	LIBSDL2IMAGEFILE = /usr/local/lib/libSDL2_image.a
	LIBSDL2TTFFILE = /usr/local/lib/libSDL2_ttf.a
	LIBSDL2MIXERFILE = /usr/local/lib/libSDL2_mixer.a
endif
ifeq ($(shell test -e $(LIBSDL2FILE) || echo -n no),no)
	RUN_INSTALL_SCRIPT = yes
else ifeq ($(shell test -e $(LIBSDL2IMAGEFILE) || echo -n no),no)
	RUN_INSTALL_SCRIPT = yes
else ifeq ($(shell test -e $(LIBSDL2TTFFILE) || echo -n no),no)
	RUN_INSTALL_SCRIPT = yes
else ifeq ($(shell test -e $(LIBSDL2MIXERFILE) || echo -n no),no)
	RUN_INSTALL_SCRIPT = yes
endif
# ====================

LIBS = $(LIB3DFLAGS) $(LIBGMATRIXFLAGS) $(LIBFTFLAGS) $(SDL_FLAGS) $(LIB_MATH) $(LIB_PTHRTEAD)

INCLUDES = -I ./include \
		-I./lib/external_log \
		-I$(LIBFT)/include \
		-I$(LIB3D)/include \
		-I$(LIBGMATRIX)/include

CFLAGS =-Wall -Wextra -Werror -march=native -O3 -flto $(LINUX_IGNOREW)
SOURCES = main.c \
			doom3d.c \
			settings.c \
			assets/cleanup.c \
			assets/cleanup_sprites_and_hud.c \
			assets/cleanup_animation3d.c \
			assets/asset_load.c \
			assets/asset_load_from_map/asset_load_from_map.c \
			assets/asset_load_from_map/key.c \
			assets/asset_load_from_map/textures.c \
			assets/asset_load_from_map/models.c \
			assets/asset_load_from_map/sdl_assets.c \
			assets/asset_write.c \
			assets/asset_size.c \
			assets/asset_loading/animations_3d.c \
			assets/asset_loading/models.c \
			assets/asset_loading/normal_maps.c \
			assets/asset_loading/textures.c \
			assets/asset_loading/sprites_and_hud.c \
			assets/asset_loading/skybox.c \
			assets/asset_loading/npcs.c \
			assets/asset_loading/lights.c \
			assets/asset_loading/triggers.c \
			assets/asset_loading/triggers_drops.c \
			assets/asset_loading/prefabs.c \
			assets/asset_loading/fonts.c \
			assets/asset_loading/sounds.c \
			assets/asset_loading/sdl_assets.c \
			assets/asset_loading/sdl_asset_size.c \
			player/player.c \
			player/player_jump.c \
			player/player_shoot.c \
			player/player_guns.c \
			player/player_reload.c \
			player/player_interact.c \
			player/collision.c \
			player/crouch.c \
			player/movement.c \
			player/movement2.c \
			player/player_limit_movement.c \
			player/player_status.c \
			player/player_vitals_render.c \
			player/player_weapons_render.c \
			player/player_flashlight.c \
			player/player_editor_init.c \
			player/player_init.c \
			projectile/projectile_init.c \
			projectile/projectile_update.c \
			projectile/projectile_collision.c \
			projectile/projectile_explosion.c \
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
			npc/npc_face_player.c \
			npc/npc_finalboss.c \
			npc/npc_special_attack.c \
			trigger/subtitles.c \
			trigger/trigger.c \
			trigger/trigger_timer.c \
			trigger/trigger_place.c \
			trigger/trigger_place2.c \
			trigger/trigger_handle.c \
			trigger/trigger_sound.c \
			trigger/trigger_place_start_end.c \
			lights/light.c \
			lights/light2.c \
			lights/light_color.c \
			path/path.c \
			path/path2.c \
			path/patrol_path.c \
			scene_objects/object_utils.c \
			scene_objects/object_is_ignored.c \
			scene_objects/object_next_index.c \
			scene_objects/object_scene_placement.c \
			scene_objects/object_scene_placement_utils.c \
			scene_objects/object_update.c \
			scene_objects/object_update_utils.c \
			scene_objects/game_end.c \
			physics/is_grounded.c \
			physics/forces_update.c \
			physics/physics_obj_utils.c \
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
			scene/scene_content.c \
			scene/camera/camera.c \
			scene/camera/update.c \
			editor/editor_selection.c \
			editor/editor_deselection.c \
			editor/editor_utils1.c \
			editor/editor_utils2.c \
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
			render/editor_guide.c \
			render/editor_ui_object_info.c \
			render/debug/debug.c \
			render/debug/debug_line.c \
			render/debug_draw_colliders.c \
			render/debug/debug_aabb.c \
			render/notifications1.c \
			render/notifications2.c \
			render/render_triangle_pool.c \
			render/transform.c \
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
			events/custom_event_handling/random.c \
			events/custom_event_handling/player/interaction.c \
			events/custom_event_handling/player/movement.c \
			events/custom_event_handling/player/weapons.c \
			events/custom_event_handling/objects/translate.c \
			events/custom_event_handling/objects/rotate.c \
			events/custom_event_handling/objects/objects.c \
			events/custom_event_handling/objects/npc.c \
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
			animations/animation_transform.c \
			animations/animation_utils.c \
			animations/animation_utils2.c

OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=.o))
DEV_OBJS = $(addprefix $(DIR_OBJ)/,$(SOURCES:.c=_dev.o))

all: intro $(DIR_OBJ) install_sdl $(NAME) usage

$(NAME): $(OBJS)
	@make libs
	@printf "\033[32;1mCompiling app...\n\033[0m"
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)

libs:
	@printf "\033[32;1mCompiling libs...\n\033[0m"
	make -C $(LIBFT)
	make -C $(LIB3D)
	make -C $(LIBGMATRIX)

usage:
	@printf "\033[32;1mDone.\n\n\033[0m"
	@printf "\033[32;1mUsage:\n ./$(NAME) [options]\n\033[0m"
	@printf "\033[32;1mOptions:\n\033[0m"
	@printf "\033[32;1m --load-assets: Loads assets from assets folder. Remember to save first level in editor. Use this after adding new assets\n\033[0m"
	@printf "\033[32;1m --convert-assets: Convert old first map format to contain assets, save first level in editor to convert\n\033[0m"
	@printf "\033[32;1m --default: Use default map format without converting to contain assets when saving\n\033[0m"
	@printf "\033[32;1m --debug: Debug mode toggled on from start\n\033[0m"

intro:
	@printf "\033[32;1mBegin doom-nukem compilation...\n\033[0m"

$(DIR_OBJ):
	@printf "\033[32;1mCreate temp directories...\n\033[0m"
	@mkdir -p temp
	@mkdir -p temp/assets
	@mkdir -p temp/assets/asset_loading
	@mkdir -p temp/assets/asset_load_from_map
	@mkdir -p temp/menus
	@mkdir -p temp/map
	@mkdir -p temp/scene
	@mkdir -p temp/scene/camera
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
	@mkdir -p temp/scene_objects
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

install_sdl:
ifeq ($(UNAME),Linux)
	@printf "\033[32;1mCheck SDL2 on Linux...\n\033[0m"
else ifeq ($(UNAME),Darwin)
	@printf "\033[32;1mCheck SDL2 on MacOS...\n\033[0m"
ifeq (,$(shell which brew))
	$(error "No brew found, install homebrew on macos for compilation to work")
endif
else
	$(error "Can only compile on Mac OS and Linux")
endif
	@printf "\033[32;1mInstall SDL2 needed? $(RUN_INSTALL_SCRIPT)...\n\033[0m"
ifeq (yes,$(RUN_INSTALL_SCRIPT))
	@printf "\033[32;1mInstalling SDL2 (and its sub libraries)...\n\033[0m"
	./install.sh
endif

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

norm: norminette $(DIR_SRC) $(LIBFT) $(LIB3D) $(LIBGMATRIX) ./include

.PHONY: all, $(DIR_OBJ), clean, fclean, intro, usage
