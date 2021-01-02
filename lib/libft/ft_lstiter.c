/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakanen <aleksi.hakanen94@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 18:14:58 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/30 15:44:55 by ahakanen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_lstiter() function iterates over all list elements
** applying a function f on each element.
*/

void	ft_lstiter(t_list *lst, void (*f)(t_list*))
{
	if (lst && f)
	{
		f(lst);
		ft_lstiter(lst->next, f);
	}
}
