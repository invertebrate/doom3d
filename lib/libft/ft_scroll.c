/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scroll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:20:13 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/14 15:22:05 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Scroll to given character in &str
*/

void					ft_scroll_to(char **str, char c)
{
	while (**str && **str != c)
		(*str)++;
}

/*
** Scroll to one over given character in &str
*/

void					ft_scroll_over(char **str, char c)
{
	ft_scroll_to(str, c);
	if (**str)
		(*str)++;
}
