/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erybolov <erybolov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:11:53 by erybolov          #+#    #+#             */
/*   Updated: 2025/02/21 22:11:56 by erybolov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mouse_handler(double xpos, double ypos, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->data.mouse_x = xpos;
	game->data.mouse_y = ypos;
}
