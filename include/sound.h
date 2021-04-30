/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 17:59:45 by phakakos          #+#    #+#             */
/*   Updated: 2021/04/30 14:36:52 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUND_H
# define SOUND_H

# ifdef __APPLE__
# include <SDL_audio.h>
# endif
# ifdef __linux__
#  include <SDL2/SDL_audio.h>
# endif

/*
** SOUND MACROS
*/

# define PREF_SAMPLES 1024
# define NUM_SOUNDS 10
# define NUM_MUSIC 1
# define NUM_SEFFECTS 20
# define PREF_AUDIO AUDIO_F32
# define PREF_CHAN 2
# define PREF_FREQ 44100
# define SOUND_DIST 100000
# define SOUNDS 20 // MUSIC + SEFFECT
# define MUSIC 2
# define SEFFECT 18
# define TRACK1 "assets/sounds/basic_music.wav"
# define TRACK2 "assets/sounds/doom_music.wav"
# define SF_SHTG_FIRE "assets/sounds/shotgun_fire.wav"
# define SF_EXPLSION "assets/sounds/boom.wav"
# define SF_PSTL_FIRE "assets/sounds/pistol.wav"
# define SF_GUN_EMPT "assets/sounds/empty_clip.wav"
# define SF_GUN_REL "assets/sounds/reload.wav"
# define SF_RPG_FIRE "assets/sounds/rpg.wav"
# define SF_FIST_FIRE "assets/sounds/melee_attack.wav"
# define SF_FIST_HIT "assets/sounds/fist.wav"
# define SF_EXPLSION2 "assets/sounds/explosion.wav"
# define SF_LANDING "assets/sounds/landing.wav"
# define SF_PICKUP "assets/sounds/pickup.wav"
# define SF_DOOR_LOCKED "assets/sounds/door_locked.wav"
# define SF_DOOR_OPEN "assets/sounds/door_open.wav"
# define SF_MONSTER_HURT "assets/sounds/monster_hurt.wav"
# define SF_MONSTER_ALERT "assets/sounds/monster_notice.wav"
# define SF_MONSTER_SHOOT "assets/sounds/monster_shoot.wav"
# define SF_PLAYER_HURT "assets/sounds/player_hurt.wav"
# define SF_CRATE_BREAK "assets/sounds/crate_break.wav"

# define SPLAYING 1
# define SPAUSED 2
# define SSTOPPED 0

/*
** SOUND STRUCTS
*/

typedef struct			s_track
{
	Uint8	*data;
	Uint32	len;
}						t_track;

typedef struct			s_sound t_sound;

typedef struct			s_sound
{
	t_track	*sound;
	Uint32	pos;
	char	state;
	char	type;
	char	loop;
	char	priority;
	float	vol;
	t_sound	*next;
}						t_sound;

typedef struct			s_mp
{
	int					channels;
	SDL_AudioSpec		auspec;
	SDL_AudioDeviceID	audev;
	t_track				*library[SOUNDS];
	t_sound				*tracks;
	t_sound				*effects;
	float				st_vol;
	float				sf_vol;
	Uint8				*stream;
	int					len;
}						t_mp;

/*
** SOUND ENUMS
*/

/*
** SOUND INDEXES
** mu_ prefix for music, sf_ for sound effects
** gun prefixes:
** shotgun = shtg_
** pistol = pstl_
*/

typedef enum			e_sounds
{
	mu_main,
	mu_doom,
	sf_shtg_fire,
	sf_explsion,
	sf_pstl_fire,
	sf_gun_empt,
	sf_gun_rel,
	sf_rpg_fire,
	sf_fist_fire,
	sf_fist_hit,
	sf_explsion2,
	sf_landing,
	sf_pickup,
	sf_door_locked,
	sf_door_open,
	sf_monster_hurt,
	sf_monster_alert,
	sf_monster_shoot,
	sf_player_hurt,
	sf_crate_break,
}						t_sounds;

/*
** SOUND TYPES
** used to differenciate different sound types, e.g. menu, in-game, death screen
** is used in functions to pause/clear all sounds of a set type
*/

typedef enum			e_sound_type
{
	st_main_menu = 1,
	st_menu,
	st_pause,
	st_game,
	st_death,
}						t_sound_type;

#endif
