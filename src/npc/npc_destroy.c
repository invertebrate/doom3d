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
    while (i < ANIM_3D_FRAME_MAX)
    {
        if (anim == NULL)
        {
            return (false);
        }
        if (anim->animation_frames == NULL)
        {
            return (false);
        }
        if (anim->animation_frames[i] != NULL)
        {
            l3d_3d_object_destroy(anim->animation_frames[i]);
        }
        i++;
    }
    free(anim);
    anim = NULL;
    return (true);
}

static t_bool 	npc_enemy_destroy(t_3d_object *npc_obj)
{
    if (npc_obj == NULL && npc_obj->type != object_type_npc)
    {
        return (false);
    }
    if (((t_npc*)npc_obj->params)->animation_3d != NULL)
    {
        return(animation_3d_destroy((((t_npc*)npc_obj->params))->animation_3d));
    }
    else
    {
        return (false);
    }
    l3d_3d_object_destroy(npc_obj);
    return (false);
}

t_bool          npc_destroy(t_3d_object *npc_obj)
{
     if (((t_npc*)npc_obj->params)->type == npc_type_default ||
        ((t_npc*)npc_obj->params)->type == npc_type_ranged)
        return (npc_enemy_destroy(npc_obj));
    else
    {
        ft_printf("NPC not destroyed: functionality not implemented yet!"
         "\nNPC type: %d, not implemented", ((t_npc*)npc_obj->params)->type);
        return false;
    }
    return (false);
}