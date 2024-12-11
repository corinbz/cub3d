/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2024/11/26 12:16:20 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Test", true);
	if (!mlx)
        mlx_show_error();

	// Try to load the file
	mlx_texture_t* texture = mlx_load_png("assets/pngs/stone.png");
	if (!texture)
	{
		printf("failed here\n");
		mlx_show_error();
	}
	
	// Convert texture to a displayable image
	mlx_image_t* img = mlx_texture_to_image(mlx, texture);
	mlx_resize_image(img,128,128);
	if (!img)
        mlx_show_error();

	// Display the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        mlx_show_error();

	mlx_loop(mlx);

	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);

        // Optional, terminate will clean up any leftover images (not textures!)
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}