/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccraciun <ccraciun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:54:18 by ccraciun          #+#    #+#             */
/*   Updated: 2024/11/26 10:42:11 by ccraciun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void mlx_error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Try to load the file
	mlx_texture_t* texture = mlx_load_png("assets/blue_brick.png");
	if (!texture)
	{
		printf("failed here\n");
		error();
	}
	
	// Convert texture to a displayable image
	mlx_image_t* img = mlx_texture_to_image(mlx, texture);
	if (!img)
        error();

	// Display the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);

        // Optional, terminate will clean up any leftover images (not textures!)
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}