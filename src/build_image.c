/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiersoh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:11:35 by abiersoh          #+#    #+#             */
/*   Updated: 2022/06/06 21:16:03 by abiersoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"


double	double_abs(double d)
{
	if (d < 0)
		return (-d);
	return (d);
}

void	build_image(t_image *img, t_data *data, t_player *player)
{

	//Initialisations
	//felt cute, might delete later
	player->posX = 10;
	player->posY = 13;
	player->dirX = -1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.66;
	int	x;

	x = -1;
	while (++x < img->width)
	{
		double	cameraX = 2 * x / (double)(W_HEIGHT) - 1;	//-1 is left, 0 middle, 1 right
		double	rayDirX = player->dirX + player->planeX * cameraX;	//X value of raydir vector.
		double	rayDirY = player->dirY + player->planeY * cameraX; //Y value of raydir vector.
		int	mapX = (int) player->posX;	//position, X Y, of where we are.
		int	mapY = (int) player->posY;
		
		double	side_dist_X;	//how much distance ray has to travel to reach next X or Y case, from player position
		double	side_dist_Y;
		double	delta_dist_X;	//how much distance ray has to travel between 2 X or Y cases.
		double	delta_dist_Y;
		double	perpWallDist;

		if (rayDirX == 0)
			delta_dist_X = HUGE_VAL;
		else
			delta_dist_X = double_abs(1 / rayDirX);
		if (rayDirY == 0)
			delta_dist_Y = HUGE_VAL;
		else
			delta_dist_Y = double_abs(1 / rayDirY);
		//stepX : -1 if ray goes left, 1 otherwise.
		//stepY : -1 if ray goes up, 1 otherwise	??
		int	stepX;
		int	stepY;
		int	hit;
		hit = 0;	//Did we hit a wall ?
		int	side;	//Which texture should we take pixel from ?
		//Calculate step and initial Sidedist
			if (rayDirX < 0)
		{
			stepX = -1;
			side_dist_X = (player->posX - mapX) * delta_dist_X;
		}
		else
		{
			stepX = 1;
			side_dist_X = (mapX + 1.0 - player->posX) * delta_dist_X;
		}
			if (rayDirY < 0)
		{
			stepY = -1;
			side_dist_Y = (player->posY - mapY) * delta_dist_Y;
		}
		else
		{
			stepY = 1;
			side_dist_Y = (mapY + 1.0 - player->posY) * delta_dist_Y;
		}
		while (!hit)
		{
			if (side_dist_X < side_dist_Y)
			{
				side_dist_X += delta_dist_X;
				mapX += stepX;
				side = EAST + (rayDirX > 0);	//east/west
			}
			else
			{
				side_dist_Y += delta_dist_Y;
				mapY += stepY;
				side = NORTH + (rayDirY > 0);	//north/south
			}
			if (data->map[mapX][mapY] == 1)
				hit = 1;
		}
		//Ray just hit a wall.
		//how much distance ray travelled ?
		if (side == 0 || side == 1)
		{
			perpWallDist = (side_dist_X - delta_dist_X);
		}
		else
		{
			perpWallDist = (side_dist_Y - delta_dist_Y);
		}
			//How much pixel we should draw, depending of wall distance.
		int	lineHeight = (int)(W_HEIGHT / perpWallDist);
			int	upperWall = (W_HEIGHT - lineHeight) / 2;
		int	lowerWall = (W_HEIGHT + lineHeight) / 2;
		if (upperWall < 0)
			upperWall = 0;
		if (lowerWall >= W_HEIGHT)
			lowerWall = W_HEIGHT - 1;
			//Which x of the wall we should draw
		double	wallX;
		if (side == 0 || side == 1)
			wallX = player->posY + perpWallDist * rayDirY;
		else
			wallX = player->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);	//0 <= wallX < 1
			draw_line(img, data, wallX, x, upperWall, lowerWall, &data->img[side]);
	}
}

void	draw_line(t_image *img, t_data *data, double wallX, int x, int upperWall, int lowerWall, t_image *texture)
{
	int	y;
	int	x_img;

	x_img = (int) (wallX * (double) texture->width);

	y = 0;

	while (y < upperWall)
	{
		pixel_put(img, x, y, data->Ccolor);
		y++;
	}

	//y : lowerWall - upperWall 
	//upperwall : 200
	//lowerwall : 400
	//y	: 250
	//y_size : 32;
	//doit renvoyer 8

	//(y - upperwall) / (lowerwall - upperwall)
	while (y < lowerWall)
	{
		pixel_put(img, x, y, get_color(texture, x_img, (y - upperWall) / (lowerWall - upperWall)));
		y++;
	}
	while (y < W_HEIGHT)
	{
		pixel_put(img, x, y, data->Fcolor);
		y++;
	}
	return ;
}
