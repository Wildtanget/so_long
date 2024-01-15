/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notahtah <notahtah@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 01:00:14 by notahtah          #+#    #+#             */
/*   Updated: 2024/01/15 01:00:14 by notahtah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "../get_next_line/get_next_line.h"

#define MLX_ERROR 1

/* Tile size*/
#define TILE_SIZE 64

/* Colors */
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF

/* Paths */
#define PLAYER "./assets/player.xmp"
#define COIN "./assets/coin.xmp"
#define EXIT "./assets/exit.xmp"
#define FLOOR "./assets/floor.xmp"
#define WALL "./assets/wall.xmp"

/* Maps */
#define MINIMAL_1 "./minimal_horizontal.ber"
#define BIG_1 "./big.ber"
#define BEURS "./beurs.ber"

typedef struct s_tiles {
    void *coin; 
    void *exit;
    void *floor;
    void *player;
    void *wall;
}   t_tiles;

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    **map;
    int     width;
    int     height;
    t_tiles tiles;
    int     coins;
}   t_data;

int     handle_no_event(void *data);
void    move_player(int keysym, t_data *data, int x, int y);
int     handle_input(int keysym, t_data *data);
int     on_destroy(t_data *data);
int     close_window(int keysym, t_data *data);
int     render(t_data *data);
void    load_sprites(t_data *data, void **image, char *path);
void    init_sprites(t_data *data);
void    load_map(t_data *data);

#endif