#include "cub3d.h"

void error_exit(const char *message, t_game *game, char *line)
{
	printf("Error\n%s\n", message);
	if (line)
        free(line);
    if (game->tex.no_path)
        free(game->tex.no_path);
    if (game->tex.so_path)
        free(game->tex.so_path);
    if (game->tex.we_path)
        free(game->tex.we_path);
    if (game->tex.ea_path)
        free(game->tex.ea_path);
	if (game->map.raw_data)
        free(game->map.raw_data);
    if (game->map.grid)
        free_matrix(game->map.grid);
	exit(1);
}
void process_line(t_game *game, char *line)
{
    int i;
    int tex_status;
	int color_status;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == '\n' || line[i] == '\0')
        return ;
    tex_status = check_texture(game, &line[i]);
    if (tex_status == 1)
        return ;
    if (tex_status == -1)
		error_exit("Could not open texture file.", game, line);
	color_status = check_color(game, &line[i]);
    if (color_status == 1)
        return ;    
	if (color_status == -1)
		error_exit("Invalid color format or value.", game, line);
    if (all_configs_are_loaded(game))
        append_to_map_grid(game, line);
    else
    {
        error_exit("Invalid identifier or map appearing too early.", game, line);
    }
}

int all_configs_are_loaded(t_game *game)
{
    /* Casteo explícito a unsigned int para coincidir con la declaración de t_tex */
    if (game->tex.no_path != NULL && game->tex.so_path != NULL &&
        game->tex.we_path != NULL && game->tex.ea_path != NULL &&
        game->tex.floor_color != (unsigned int)-1 && 
        game->tex.ceiling_color != (unsigned int)-1)
    {
        return (1);
    }
    return (0);
}

static void parse_map(t_game *game, int fd)
{
    char *line;
	char **map_copy;

    while ((line = get_next_line(fd)) != NULL)
    {
        process_line(game, line);
        free(line);
    }
	if (!game->map.raw_data)
        error_exit("No map content found in file.", game, NULL);
    game->map.grid = ft_split(game->map.raw_data, '\n');
    free(game->map.raw_data);
    game->map.raw_data = NULL;
	if (!game->map.grid)
        error_exit("Malloc failed allocating map grid.", game, NULL);
    if (scan_map_characters(game) == -1)
        error_exit("Invalid map characters or wrong number of players.", game, NULL);
    map_copy = duplicate_matrix(game->map.grid);
    if (!map_copy)
        error_exit("Malloc failed allocating map copy.", game, NULL);
    flood_fill(game, map_copy, game->player.pos_y, game->player.pos_x);
    free_matrix(map_copy);
}

static void parse_cub(t_game *game, char *filename)
{
    int fd;

    if (check_file_extension(filename, ".cub") == 0)
    {
        printf("Error\nInvalid file extension. Expected .cub\n");
        exit(1);
    }
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("Error\nCould not open file.\n");
        exit(1);
    }
    parse_map(game, fd);
    close(fd);
}
static void init_struct(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->tex.floor_color = -1;  
	game->tex.ceiling_color = -1;
	game->map.raw_data = NULL;
	game->map.grid = NULL;
}

int	main (int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Error\nInvalid number of arguments.\n");
		return 1;
	}
	t_game game;
	init_struct(&game);
	parse_cub(&game, argv[1]);
	//init_mlx(&game);
	//start_game(&game);
	return 0;
}