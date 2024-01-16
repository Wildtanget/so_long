/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notahtah <notahtah@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 00:59:42 by notahtah          #+#    #+#             */
/*   Updated: 2024/01/15 00:59:42 by notahtah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../get_next_line/get_next_line.h"

int main(void)
{
    t_data data;
    
    /* Initialize window */
    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (MLX_ERROR);

    init_sprites(&data);
    load_map(&data);
    data.win_ptr = mlx_new_window(data.mlx_ptr, data.width * TILE_SIZE, data.height * TILE_SIZE, "Window");
    if (!data.win_ptr)  
    {
        free(data.mlx_ptr);
        return (MLX_ERROR);
    }
    /* Create image*/

    /* Setup hooks */
    mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_input, &data);
    mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
    mlx_loop_hook(data.mlx_ptr, &render, &data);

    /* Loop window */
    mlx_loop(data.mlx_ptr);

    return (0);
}

int handle_no_event(void *data)
{
	data = data;
    return (0);
}

void move_player(int keysym, t_data *data, int x, int y)
{
    int i;
    int j;
    int player_pos[2];

    printf("Pressed %d.\n", keysym);
    i = 0;
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
            if (data->map[i][j] == 'P')
            {
                player_pos[0] = j;
                player_pos[1] = i;
            }
            j++;
        }
        i++;
    }
    if (data->map[player_pos[1] + x][player_pos[0] + y] != '1' && data->map[player_pos[1] + x][player_pos[0] + y] != 'E')
    {
        data->map[player_pos[1]][player_pos[0]] = '0';
        data->map[player_pos[1] + x][player_pos[0] + y] = 'P';
    }
    else if (data->map[player_pos[1] + x][player_pos[0] + y] == 'E' && data->coins == 0)
        on_destroy(data);
}

int handle_input(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
    {
        printf("Pressed %d (esc).\n", keysym);
        close_window(keysym, data);
    }
    else if (keysym == XK_a || keysym == XK_Left)
        move_player(keysym, data, 0, -1);
    else if (keysym == XK_d || keysym == XK_Left)
        move_player(keysym, data, 0, 1);
    else if (keysym == XK_w || keysym == XK_Up)
        move_player(keysym, data, -1, 0);
    else if (keysym == XK_s || keysym == XK_Down)
        move_player(keysym, data, 1, 0);
    return (0);
}

int on_destroy(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (0);
}

int close_window(int keysym, t_data *data)
{
	keysym = keysym;
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    mlx_destroy_display(data->mlx_ptr);
    free(data->mlx_ptr);
    exit(0);
    return (0);
}   

int render(t_data *data)
{
    int i;
    int j;

    data->coins = 0;
    i = 0;
    j = 0;
    while (i < data->height)
    {
        j = 0;
        while (j < data->width)
        {
            if (data->map[i][j] == '1')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles.wall, j * TILE_SIZE, i * TILE_SIZE);
            else if(data->map[i][j] == 'P')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles.player, j * TILE_SIZE, i * TILE_SIZE);
            else if(data->map[i][j] == 'C')
            {
                data->coins++;
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles.coin, j * TILE_SIZE, i * TILE_SIZE);
            }
            else if(data->map[i][j] == 'E')
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles.exit, j * TILE_SIZE, i * TILE_SIZE);
            else
                mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles.floor, j * TILE_SIZE, i * TILE_SIZE);
            j++;
        }
        i++;
    }
    return (0);
}

void load_sprites(t_data *data, void **image, char *path)
{
    int width;
    int height;

    *image = mlx_xpm_file_to_image(data->mlx_ptr, path, &width, &height);
}

void init_sprites(t_data *data)
{
    load_sprites(data, &data->tiles.coin, COIN);
    load_sprites(data, &data->tiles.wall, WALL);
    load_sprites(data, &data->tiles.player, PLAYER);
    load_sprites(data, &data->tiles.exit, EXIT);
    load_sprites(data, &data->tiles.floor, FLOOR);
}

/*  Read and load map   */
void load_map(t_data *data)
{
    int fd;
    int i;
    char *line;
    int j;

    fd = open(BIG_1, O_RDONLY);
    if (fd == -1)
        exit(1);
    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        data->map[i] = line;
        line = get_next_line(fd);
        i++;
    }
    data->height = i;
    j = 0;
    while (data->map[i - 1][j])
        j++;
    data->width = j;
    close(fd);
}
