/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cub3d                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27                               #+#    #+#             */
/*   Updated: 2026/06/27                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** ft_strlen - Calcula la longitud de una cadena
** @str: Cadena a medir
**
** Return: Longitud de la cadena
*/
int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/*
** ft_strdup - Duplica una cadena en memoria dinámica
** @str: Cadena a duplicar
**
** Return: Puntero a la nueva cadena o NULL si falla
*/
char	*ft_strdup(char *str)
{
	char	*dup;
	int		i;

	if (!str)
		return (NULL);
	dup = malloc(ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
** ft_strtrim - Elimina espacios al inicio y final de una cadena
** @str: Cadena a limpiar
**
** Return: Nueva cadena sin espacios o NULL si falla
*/
char	*ft_strtrim(char *str)
{
	int		start;
	int		end;
	char	*trimmed;
	int		i;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')
		start++;
	end = ft_strlen(str) - 1;
	while (end > start && (str[end] == ' ' || str[end] == '\t'
			|| str[end] == '\n'))
		end--;
	trimmed = malloc(end - start + 2);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (start <= end)
		trimmed[i++] = str[start++];
	trimmed[i] = '\0';
	return (trimmed);
}

/*
** ft_strncmp - Compara n caracteres de dos cadenas
** @s1: Primera cadena
** @s2: Segunda cadena
** @n: Número de caracteres a comparar
**
** Return: 0 si son iguales, diferencia si no
*/
int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

/*
** get_next_line - Lee una línea de un file descriptor
** @fd: File descriptor a leer
**
** Return: Línea leída o NULL si termina o hay error
*/
char	*get_next_line(int fd)
{
	static char	buffer[1024];
	static int	buffer_pos;
	static int	buffer_read;
	char		line[1024];
	int			i;

	i = 0;
	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, 1024);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		line[i] = buffer[buffer_pos++];
		if (line[i] == '\n')
		{
			line[++i] = '\0';
			return (ft_strdup(line));
		}
		i++;
	}
	if (i > 0)
	{
		line[i] = '\0';
		return (ft_strdup(line));
	}
	return (NULL);
}
