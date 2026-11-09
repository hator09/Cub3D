#include "cub3d.h"

void free_matrix(char **matrix)
{
    int i;

    if (!matrix)
        return ;
    i = 0;
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}

char **duplicate_matrix(char **matrix)
{
	int     rows;
	int     i;
	char    **copy;

	if (!matrix)
		return (NULL);
	rows = 0;
	while (matrix[rows])
		rows++;
	copy = malloc(sizeof(char *) * (rows + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		copy[i] = ft_strdup(matrix[i]);
		if (!copy[i])
		{
			free_matrix(copy);
			return (NULL);
		}
		i++;
	}
	copy[rows] = NULL;
	return (copy);
}
static void set_player_spawn(t_game *game, int x, int y, int *players)
{
    game->player.pos_x = x;
    game->player.pos_y = y;
    game->map.p_dir = game->map.grid[y][x];
    (*players)++;
}
int scan_map_characters(t_game *game)
{
    int x;
    int y;
    int players;

    players = 0;
    y = 0;
    while (game->map.grid[y])
    {
        x = 0;
        while (game->map.grid[y][x])
        {
            if (!ft_strchr(" 012NSEW", game->map.grid[y][x]))
                return (-1);
            if (ft_strchr("NSEW", game->map.grid[y][x]))
                set_player_spawn(game, x, y, &players);
            x++;
        }
        y++;
    }
    game->map.height = y;
	if(players == 1)
        return (1);
    return (-1);
}

void flood_fill(t_game *game, char **copy, int y, int x)
{
    if (y < 0 || y >= game->map.height || x < 0 || x >= (int)ft_strlen(copy[y]))
    {
        free_matrix(copy);
        error_exit("Map boundary is open to the void.", game, NULL);
    }
    if (copy[y][x] == ' ')
    {
        free_matrix(copy);
        error_exit("Map contains a breach opening to spaces.", game, NULL);
    }
    if (copy[y][x] == '1' || copy[y][x] == 'V')
        return ;
    copy[y][x] = 'V';

    flood_fill(game, copy, y - 1, x); /* Norte */
    flood_fill(game, copy, y + 1, x); /* Sur */
    flood_fill(game, copy, y, x - 1); /* Oeste */
    flood_fill(game, copy, y, x + 1); /* Este */
}

void append_to_map_grid(t_game *game, char *line)
{
    char *temp;

    if (!game->map.raw_data && (line[0] == '\n' || line[0] == '\0'))
        return ;

    if (!game->map.raw_data)
    {
        game->map.raw_data = ft_strdup(line);
    }
    else
    {
        temp = ft_strjoin(game->map.raw_data, line);
        free(game->map.raw_data);
        game->map.raw_data = temp;
    }
    if (!game->map.raw_data)
        error_exit("Malloc failed allocating map.", game, line);
}
