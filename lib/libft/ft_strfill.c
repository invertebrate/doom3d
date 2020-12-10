/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:02:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/24 20:16:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strfill fills string with character c
*/

void	ft_strfill(char **str, char c, size_t len)
{
	size_t	i;

	if (!str || !c || len == false)
		return ;
	i = 0;
	while (i < len)
	{
		(*str)[i] = c;
		i++;
	}
}
