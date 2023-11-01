/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lionel <lionel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:42:51 by lclerc            #+#    #+#             */
/*   Updated: 2023/11/01 12:11:17 by lionel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	print_struct(t_file_data *data)
{
	int	i;
	int	j;

	printf("North Texture: %s\n", data->north_texture);
	printf("South Texture: %s\n", data->south_texture);
	printf("West Texture: %s\n", data->west_texture);
	printf("East Texture: %s\n", data->east_texture);
	printf("Floor Color: %s\n", data->floor_color);
	printf("Ceiling Color: %s\n", data->ceiling_color);
	printf("Player Spawn Direction: %s\n", data->player_spawn_direction);
	printf("Player X Coordinate: %lf\n", data->player_x);
	printf("Player Y Coordinate: %lf\n", data->player_y);
	printf("File Descriptor: %d\n", data->file_descriptor);
	printf("Return Value: %d\n", data->return_value);
	printf("Floor RGB: R(%d) G(%d) B(%d)\n", data->floor_rgb.red,
		data->floor_rgb.green, data->floor_rgb.blue);
	printf("Ceiling RGB: R(%d) G(%d) B(%d)\n", data->ceiling_rgb.red,
		data->ceiling_rgb.green, data->ceiling_rgb.blue);
	if (data->map_as_array)
	{
		printf("Map Content:\n");
		i = 0;
		while (data->map_as_array[i] != NULL)
		{
			j = 0;
			printf("Line :%02d: -> ", i);
			while (data->map_as_array[i][j] != NEW_LINE)
			{
				if (data->map_as_array[i][j] == EMPTY)
					printf("\033[0;32m%d\033[0m", data->map_as_array[i][j]);
				else if (data->map_as_array[i][j] == FLOOR)
					printf("\033[0;33m%d\033[0m", data->map_as_array[i][j]);
				else if (data->map_as_array[i][j] == WALL)
					printf("\033[0;31m%d\033[0m", data->map_as_array[i][j]);
				j++;
			}
			printf(":%d:\n", data->map_as_array[i][j]);
			i++;
		}
	}
	else
	{
		printf("Map Content: (Empty)\n");
	}
}

/**
 * @brief Remove leading white spaces from a string.
 *
 * This function removes leading white spaces (spaces and tabs) from a string.
 *
 * @param string The string to process.
 * @return A pointer to the string with leading white spaces removed.
 */
char	*skip_leading_white_spaces(char *string)
{
	while (string && *string != '\0' && (*string == '\t' || *string == '\v'
			|| *string == '\f' || *string == '\r' || *string == ' '
			|| *string == '\n'))
		string++;
	return (string);
}

/**
 * @brief Initializes a structure with zeros.
 *
 * This function initializes the memory pointed to by `structure_pointer` with
 * zeros, effectively setting all its members to zero values. It's commonly used
 * to prepare structures for use.
 *
 * @param structure_pointer A pointer to the structure to be initialized.
 */
void	initialize_struct(t_file_data *structure_pointer)
{
	ft_bzero(structure_pointer, sizeof(*structure_pointer));
}

void	print_parsing_error_message_2(t_return_value error)
{
	if (error == NO_ELEMENT_FOUND)
		ft_putstr_fd(
			"Error\nCub file not properly formatted\n", 2);
	else if (error == PLAYER_DATA_INCORRECT_OR_MISSING)
		ft_putstr_fd(
			"Error\nPlayer data incorrect or missing\n", 2);
	else if (error == GARBAGE_DATA)
		ft_putstr_fd("Error\nMap contains garbage data\n",
			2);
	else if (error == MAP_CONTAINS_EMPTY_LINE)
		ft_putstr_fd(
			"Error\nMap contains at least an empty line\n",
			2);
	else if (error == WALL_IS_BREACHED)
		ft_putstr_fd("Error\nWall is breached\n", 2);
	else if (error == INVALID_COLORS)
		ft_putstr_fd("Error\nInvalid RGB values\n", 2);
	else if (error == DUPLICATE_ELEMENT)
		ft_putstr_fd("Error\nDuplicate element\n", 2);
}

/**
 * @brief Prints an error message based on the error code.
 *
 * This function prints an error message to the standard error (stderr) stream
 * based on the provided error code. The error messages are related to specific
 * error conditions such as memory allocation failure, file open failure, or
 * invalid file content.
 *
 * @param error The error code representing the specific error condition.
 */
void	print_parsing_error_message(t_return_value error)
{
	if (error == MALLOC_FAILURE)
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
	else if (error == NEED_MAP_CUB_FILE)
		ft_putstr_fd("Error\nUsage: use cub file\n", 2);
	else if (error == FILE_IS_EMPTY)
		ft_putstr_fd("Error\nfile is empty\n", 2);
	else if (error == FILE_OPEN_FAILURE)
		ft_putstr_fd("Error\nfile open failure\n", 2);
	else if (error == MAP_CONTENT_NOT_VALID)
		ft_putstr_fd("Error\nfile content not valid\n",
			2);
	else if (error == INVALID_ARGUMENT)
		ft_putstr_fd("Error\nUsage: use cub file\n", 2);
	else if (error == MISSING_ELEMENTS)
		ft_putstr_fd("Error\nSome elements are missing\n", 2);
	else 
		print_parsing_error_message_2(error);
}
/**
 * @brief Frees memory allocated for parsed data.
 *
 * This function is responsible for cleaning up memory allocated during the
 * parsing process, including textures, colors, file content, and the map array.
 *
 * @param data A pointer to the t_file_data structure.
 */
void	clean_up_parsing(t_file_data *data)
{
	int	i;

	i = 0;
	if (data->north_texture)
		free(data->north_texture);
	if (data->south_texture)
		free(data->south_texture);
	if (data->west_texture)
		free(data->west_texture);
	if (data->east_texture)
		free(data->east_texture);
	if (data->floor_color)
		free(data->floor_color);
	if (data->ceiling_color)
		free(data->ceiling_color);
	if (data->file_content_as_string)
		free(data->file_content_as_string);
	if (data->map_as_array)
	{
		while (data->map_as_array[i])
		{
			free(data->map_as_array[i]);
			i++;
		}
		free(data->map_as_array);
	}
}

void	print_int_grid(int **grid, int height, int width)
{
	int	i;
	int	j;

	printf("PrintingCharGrid! Height: %i and Width: %i\n", height, width);
	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			printf(":%s:", ft_itoa(grid[j][i]));
			i++;
		}
		printf("\n");
		j++;
	}
	printf("FINISHED PRINTING\n");
}
