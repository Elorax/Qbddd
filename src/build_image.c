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
	player->dirX = 1;
	player->dirY = 0;
	player->planeX = 0;
	player->planeY = 0.66;
	int	x;

	x = -1;
	while (++x < 800)
	{
		double	cameraX = 2 * x / (double)(W_HEIGHT) - 1;	//-1 is left, 0 middle, 1 right
		printf("cameraX : %f\n", cameraX);
		double	rayDirX = player->dirX + player->planeX * cameraX;	//X value of raydir vector.
		double	rayDirY = player->dirY + player->planeY * cameraX; //Y value of raydir vector.
		printf("ray X, Y : %f, %f\n", rayDirX, rayDirY);
		
		int	mapX = (int) player->posX;	//position, X Y, of where we are.
		int	mapY = (int) player->posY;
		printf("mapX, mapY : %d, %d\n", mapX, mapY);
		
		double	side_dist_X;	//how much distance ray has to travel to reach next X or Y case, from player position
		double	side_dist_Y;
		double	delta_dist_X;	//how much distance ray has to travel between 2 X or Y cases.
		double	delta_dist_Y;
		double	perpWallDist;
		
		if (rayDirX == 0)
			delta_dist_X = 1e30;
		else
			delta_dist_X = double_abs(1 / rayDirX);
		if (rayDirY == 0)
			delta_dist_Y = 1e30;
		else
			delta_dist_Y = double_abs(1 / rayDirY);
		printf("delta dist X, Y : %f, %f\n", delta_dist_X, delta_dist_Y);
		//stepX : -1 if ray goes left, 1 otherwise.
		//stepY : -1 if ray goes up, 1 otherwise
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
		printf("side dist X, Y : %f, %f\n", side_dist_X, side_dist_Y);
		printf("step X, Y : %d, %d\n", stepX, stepY);



		while (!hit)
		{
			if (side_dist_X < side_dist_Y)
			{
				side_dist_X += delta_dist_X;
				mapX += stepX;
				side = NORTH + (rayDirX > 0);	//east/west
			}
			else
			{
				side_dist_Y += delta_dist_Y;
				mapY += stepY;
				side = EAST + (rayDirY > 0);	//north/south
			}
			printf("side dist X, Y : %f, %f\n", side_dist_X, side_dist_Y);
			if (data->map[mapY][mapX] == '1')
			{
				hit = 1;
				printf("Hit : Map : %c\n", data->map[mapY][mapX]);
				printf("X, Y : %d, %d\n", mapX, mapY);
			}
			else
			{
				printf("Not hit. map : %c\n", data->map[mapY][mapX]);
				printf("X, Y : %d, %d\n", mapX, mapY);
			}
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
		printf("side : %d\ndistWall : %f\n", side, perpWallDist);
			//How much pixel we should draw, depending of wall distance.
		int	lineHeight = (int)(W_HEIGHT / perpWallDist);
			int	upperWall = (W_HEIGHT - lineHeight) / 2;
		int	lowerWall = (W_HEIGHT + lineHeight) / 2;
		if (upperWall < 0 || upperWall >= W_HEIGHT)
			upperWall = 0;
		if (lowerWall >= W_HEIGHT || lowerWall < 0)
			lowerWall = W_HEIGHT - 1;
			//Which x of the wall we should draw
		printf("lineheight, upper, lower : %d, %d, %d\n", lineHeight, upperWall, lowerWall);
		double	wallX;
		if (side == 2 || side == 3)
			wallX = (double) player->posY + perpWallDist * rayDirY;
		else
			wallX = (double) player->posX + perpWallDist * rayDirX;
		printf("posY : %f\ndistWall : %f\n rayDirY : %f\n", player->posY, perpWallDist, rayDirY);
		printf("WallX avant floor : %f\n", wallX);
		wallX -= floor(wallX);	//0 <= wallX < 1
		printf("wallX : %f\n", wallX);
		draw_line(img, data, wallX, x, upperWall, lowerWall, &data->img[side]);
	}
	printf("fini\n");
}

void	draw_line(t_image *img, t_data *data, double wallX, int x, int upperWall, int lowerWall, t_image *texture)
{
	int	y;
	int	x_img;

	x_img = floor(wallX * (double) texture->width);
	if (x_img < 0)
		x_img = 0;
	if (x_img >= texture->width)
		x_img = texture->width - 1;

	y = 0;
//	usleep(1000);
	while (y < upperWall)
	{
//		printf("%#x ??\n", data->Ccolor);
		//pixel_put(img, x, y, data->Ccolor);

		pixel_put(img, x, y, 0x000000FF);
	//	pixel_put(img, x, y, 0x00FF0000);
		y++;
	}
	//y : lowerWall - upperWall 
	//upperwall : 200
	//lowerwall : 400
	//y	: 250
	//y_size : 32;
	//doit renvoyer 8

	//(y - upperwall) / (lowerwall - upperwall)

	//usleep(1000);
	while (y < lowerWall)
	{
//		printf("%#x\n", get_color(texture, x, y));
		pixel_put(img, x, y, get_color(texture, x_img, (y - upperWall) / (lowerWall - upperWall)));
	//	pixel_put(img, x, y, 0x00FF0000);
		y++;
	}
	//usleep(1000);
	while (y < W_HEIGHT)
	{
//		printf("%#x !!\n", data->Fcolor);
		pixel_put(img, x, y, data->Fcolor);
	//	pixel_put(img, x, y, 0x00FF0000);
		y++;

	}
	return ;
}
