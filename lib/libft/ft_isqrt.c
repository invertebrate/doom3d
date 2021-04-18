/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isqrt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:53:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:45:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isqrt returns integer square root of num.
*/
int	ft_isqrt(int num)
{
	int	n;
	int	n1;

	if (0 == num)
		return (0);
	n = (num / 2) + 1;
	n1 = (n + (num / n)) / 2;
	while (n1 < n)
	{
		n = n1;
		n1 = (n + (num / n)) / 2;
	}
	return (n);
}
