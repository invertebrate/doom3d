/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_capitalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:34:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/03/11 17:26:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_capitalize(char *str)
{
	int		i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
}

void		ft_uncapitalize(char *str)
{
	int		i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
		str[i] = ft_tolower(str[i]);
}
