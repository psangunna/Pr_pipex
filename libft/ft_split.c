/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:14:24 by pamela            #+#    #+#             */
/*   Updated: 2024/04/14 19:15:06 by pamela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/* Helper function to count the words in a string*/
static size_t	count_words(char const *str, char delimiter)
{
	size_t	word_count;
	size_t	index;

	word_count = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] != delimiter)
		{
			word_count++;
			while (str[index] && str[index] != delimiter)
				index++;
		}
		else if (str[index] == delimiter)
			index++;
	}
	return (word_count);
}

/* Helper function to get the length of a word */
static size_t	get_word_length(char const *str, char delimiter)
{
	size_t	length;

	length = 0;
	while (str[length] && str[length] != delimiter)
		length++;
	return (length);
}

/* Helper function to free the memory of an array of strings */
static void	free_string_array(size_t size, char **array)
{
	while (size > 0)
	{
		size--;
		free(array[size]);
	}
	free(array);
}

/* Helper function to split a string into an array of substrings */
static char	**split_string(char const *str, char delimiter,
		char **array, size_t word_count)
{
	size_t	str_index;
	size_t	array_index;

	str_index = 0;
	array_index = 0;
	while (array_index < word_count)
	{
		while (str[str_index] && str[str_index] == delimiter)
			str_index++;
		array[array_index] = ft_substr(str, str_index,
				get_word_length(&str[str_index], delimiter));
		if (!array[array_index])
		{
			free_string_array(array_index, array);
			return (0);
		}
		while (str[str_index] && str[str_index] != delimiter)
			str_index++;
		array_index++;
	}
	array[array_index] = NULL;
	return (array);
}

/* Main function to split a string into an array of substrings */
char	**ft_split(char const *str, char delimiter)
{
	char	**array;
	size_t	word_count;

	if (!str)
		return (0);
	word_count = count_words(str, delimiter);
	array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!array)
		return (0);
	array = split_string(str, delimiter, array, word_count);
	return (array);
}
