/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:57:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:46:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_lstdelone() function deletes a one list element
** using a given delete function
*/
void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	if ((*alst)->content)
		del((*alst)->content, (*alst)->content_size);
	ft_memdel((void*)alst);
}
