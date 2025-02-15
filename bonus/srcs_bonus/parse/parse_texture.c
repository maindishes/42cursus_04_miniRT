/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 01:26:17 by jihoh             #+#    #+#             */
/*   Updated: 2022/08/12 03:22:39 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_xpm_to_mlx(t_xpm_img *xpm_img, char *xpm_file, void *mlx)
{
	if (xpm_file && ft_strcmp(xpm_file, "NULL"))
	{
		if (!ft_strncmp((xpm_file + ft_strlen(xpm_file) - 3), ".xpm", 3))
			put_error("texture file format must be .xpm", xpm_file);
		xpm_img->ptr = mlx_xpm_file_to_image(mlx,
				xpm_file, &xpm_img->w, &xpm_img->h);
		if (!xpm_img->ptr)
			put_error("fail to handle xpm file", xpm_file);
		xpm_img->addr = mlx_get_data_addr(xpm_img->ptr,
				&xpm_img->bpp, &xpm_img->size, &xpm_img->endian);
		if (!xpm_img->addr)
			put_error("fail to handle xpm file", xpm_file);
	}
	else
	{
		xpm_img->ptr = NULL;
		xpm_img->addr = NULL;
	}
}

t_texture	*get_texture_node(char *id, char *img_file,
		char *bmp_file, void *mlx)
{
	t_texture	*texture;

	texture = ft_malloc(sizeof(t_texture));
	texture->id = id;
	set_xpm_to_mlx(&texture->img_map, img_file, mlx);
	set_xpm_to_mlx(&texture->bmp_map, bmp_file, mlx);
	texture->next = NULL;
	return (texture);
}

char	*texture_element(char **pstr)
{
	char	*str;

	next(pstr);
	str = *pstr;
	while (**pstr && **pstr != 9 && **pstr != 32)
		(*pstr)++;
	return (ft_strndup(str, *pstr - str));
}

t_texture	*search_texture(t_texture *texture, char *id)
{
	while (texture)
	{
		if (!ft_strcmp(texture->id, id))
			return (texture);
		texture = texture->next;
	}
	return (NULL);
}

void	parse_texture(t_scene *scene, char **pstr, void *mlx, char *error_line)
{
	char		*id;
	char		*img_file;
	char		*bmp_file;
	t_texture	*new;

	id = texture_element(pstr);
	img_file = texture_element(pstr);
	bmp_file = texture_element(pstr);
	new = get_texture_node(id, img_file, bmp_file, mlx);
	if (!scene->texture)
		scene->texture = new;
	else if (!search_texture(scene->texture, id))
	{
		new->next = scene->texture;
		scene->texture = new;
	}
	else
		put_error("texture id is overlapped", error_line);
	free(img_file);
	free(bmp_file);
}
