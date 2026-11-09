#include "cub3d.h"

int check_color(t_game *game, char *line)
{
	int status;

	status = 0;
    if (ft_strncmp(line, "F ", 2) == 0)
        status = extract_color(game, line + 2, 'F');
    else if (ft_strncmp(line, "C ", 2) == 0)
        status = extract_color(game, line + 2, 'C');
    else
        return (0);
    return (status);
}

int parse_rgb(char **rgb)
{
    int r;
    int g;
    int b;

    /* Validamos que existan exactamente 3 valores separados por comas */
    if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3] != NULL)
        return (-1);
        
    r = ft_atoi(rgb[0]);
    g = ft_atoi(rgb[1]);
    b = ft_atoi(rgb[2]);
    
    /* El rango RGB debe estar estrictamente acotado entre 0 y 255[cite: 5] */
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (-1);
        
    /* Empaquetamos los colores en un entero de 32 bits */
    return ((r << 16) | (g << 8) | b);
}

int extract_color(t_game *game, char *line, char type)
{
    char    **rgb;
    int     color;
    int     i;

    rgb = ft_split(line, ',');
    color = parse_rgb(rgb);
    i = 0;
    while (rgb && rgb[i])
        free(rgb[i++]);
    free(rgb);
    if (color == -1)
        return (-1);
    if (type == 'F')
        game->tex.floor_color = color;
    else if (type == 'C')
        game->tex.ceiling_color = color;   
    return (1);
}



