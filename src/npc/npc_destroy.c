/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npc_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo     <veilo@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 18:32:11 by veilo             #+#    #+#             */
/*   Updated: 2021/03/14 18:32:11 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool   animation_3d_destroy(t_animation_3d *anim)
{
    uint32_t     i;

    i = 0;
    // while (i < ANIM_3D_FRAME_MAX) //i < 512
    // {
    //     // ft_printf("while i: %d\n", i);//i == 0
    //     if (anim == NULL)
    //     {
    //         ft_printf("anim was null\n");//doesnt print
    //         return (false);
    //     }
    //     if (anim->animation_frames == NULL)
    //     {
    //         ft_printf("anim frames array was null\n");//doesnt print
    //         return (false);
    //     }
    //     ft_printf("here before segfault i: %d\n", i);//prints
    //     // ft_printf("anim frame [i] %p\n", anim->animation_frames);
    //     if (anim->animation_frames[i] != NULL)//this segfaults, i == 0
    //     {
    //         ft_printf("destroying frame number %d / %d\n", i, ANIM_3D_FRAME_MAX);//doesnt print
    //         l3d_3d_object_destroy(anim->animation_frames[i]);
    //     }
    //     i++;
    // }
    // ft_printf("freeing anim3d\n");
    free(anim);
    anim = NULL;
    // ft_printf("freed and nulled anim3d\n");
    return (true);
    (void)i;
}

static t_bool 	npc_enemy_destroy(t_3d_object *npc_obj)
{
    if (npc_obj == NULL && npc_obj->type != object_type_npc)
    {
        // ft_printf("destroy npc enemy failed: npc_obj was null or obj wasn't an npc\n");
        return (false);
    }
    if (((t_npc*)npc_obj->params)->animation_3d != NULL)
        {
            // ft_printf("animation3d destroy %p\n", ((t_npc*)npc_obj->params)->animation_3d);
            animation_3d_destroy(((t_npc*)npc_obj)->animation_3d);
        }
    else
    {
        // ft_printf("destroy npc enemy failed: npc_obj did not have animation_3d\n");
        return (false);
    }
    // l3d_3d_object_destroy(npc_obj);
    // ft_printf("successfully destroyed npc enemy\n");
    return (true);
	(void)npc_obj;
}

t_bool          npc_destroy(t_3d_object *npc_obj)
{
    // ft_printf("npc destroy \n");
    npc_enemy_destroy(npc_obj);
    (void)npc_enemy_destroy;
    (void)npc_obj;
    return (true);
}