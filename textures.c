#include "cub3d.h"

char *extract_path(char *line)
{
    char *path;
    int len;
    int fd;
    int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;

    len = ft_strlen(&line[i]);
    if (len > 0 && line[i + len - 1] == '\n')
        line[i + len - 1] = '\0';
    path = ft_strdup(&line[i]);
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        free(path);
        return (NULL);
    }
    close(fd);
    
    return (path);
}

int check_file_extension(const char *filepath, const char *extension)
{
	size_t filepath_len;
	size_t extension_len;
	
	if (!filepath || !extension)
		return 0;
	filepath_len= ft_strlen(filepath);
	extension_len = ft_strlen(extension);
	if (filepath_len <= extension_len)
		return 0;
	if (ft_strncmp(filepath + filepath_len - extension_len, extension, extension_len) == 0)
		return 1;
	else
		return 0;
}

int check_texture(t_game *game, char *line)
{
    char *temp_path;

    temp_path = NULL;
    if (ft_strncmp(line, "NO ", 3) == 0 && game->tex.no_path == NULL)
    {
        temp_path = extract_path(line + 3);
        game->tex.no_path = temp_path;
    }
    else if (ft_strncmp(line, "SO ", 3) == 0 && game->tex.so_path == NULL)
    {
        temp_path = extract_path(line + 3);
        game->tex.so_path = temp_path;
    }
    else if (ft_strncmp(line, "WE ", 3) == 0 && game->tex.we_path == NULL)
    {
        temp_path = extract_path(line + 3);
        game->tex.we_path = temp_path;
    }
    else if (ft_strncmp(line, "EA ", 3) == 0 && game->tex.ea_path == NULL)
    {
        temp_path = extract_path(line + 3);
        game->tex.ea_path = temp_path;
    }
    else
        return (0);
    if (temp_path == NULL)
        return (-1); 
    return (1);
}

