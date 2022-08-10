/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 00:02:59 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/11 07:08:14 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	complementary_color(int clr)
{
	int		r;
	int		g;
	int		b;

	r = 0xFF - (clr >> 0x10);
	g = 0xFF - (clr >> 0x08 & 0xFF);
	b = 0xFF - (clr & 0xFF);
	return ((r << 0x10) | (g << 0x08) | b);
}

int	checker_board_pattern_at(double u, double v, t_hit hit)
{
	int	u2;
	int	v2;
	int	res;

	u2 = u * hit.elem.checker_w;
	v2 = v * hit.elem.checker_h;
	res = (u2 + v2) % 2;
	if (res)
		return (hit.elem.clr);
	else
		return (complementary_color(hit.elem.clr));
}
