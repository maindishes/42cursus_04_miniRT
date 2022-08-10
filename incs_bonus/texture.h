/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 02:35:02 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/09 00:10:07 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "struct.h"
# include "vec3.h"
# include <math.h>

int	checker_board(t_hit hit);
int	complementary_color(int clr);
int	uv_pattern_at(double u, double v, t_hit hit);

#endif