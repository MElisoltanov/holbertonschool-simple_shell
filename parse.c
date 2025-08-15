#include "shell.h"

/**
 * tokenize - Splits a line into tokens (words)
 * @line: The input line to split
 *
 * Return: Null-terminated array of tokens
 */
char **tokenize(char *line)
{
	int bufsize = 64;
	int i = 0;
	char **tokens = NULL;
	char *token = NULL;

	tokens = malloc(sizeof(char *) * bufsize);
	if (tokens == NULL)
	{
		perror("allocation");
		return (NULL);
	}

	token = strtok(line, TOKEN_DELIMS);
	while (token != NULL)
	{
		if (i + 1 >= bufsize)
		{
			int newsize = bufsize * 2;
			char **tmp = NULL;

			tmp = realloc(tokens, sizeof(char *) * newsize);
			if (tmp == NULL)
			{
				free(tokens);
				perror("realloc");
				return (NULL);
			}
			tokens = tmp;
			bufsize = newsize;
		}

		tokens[i] = token;
		i++;

		token = strtok(NULL, TOKEN_DELIMS);
	}

	tokens[i] = NULL;
	return (tokens);
}

/**
 * count_tokens - Counts the number of tokens in a string.
 * @line: The string to count the tokens from.
 *
 * This function uses a temporary copy of the input string to safely count
 * the number of tokens without modifying the original.
 *
 * Return: The number of tokens found.
 */
size_t count_tokens(const char *line)
{
	char *line_copy = NULL;
	char *token = NULL;
	size_t count = 0;

	if (line == NULL || *line == '\0')
		return (0);
	line_copy = strdup(line);
	if (line_copy == NULL)
	{
		perror("strdup");
		return (0);
	}
	token = strtok(line_copy, " \t\r\n");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t\r\n");
	}
	free(line_copy);
	return (count);
}

/**
 * free_tokens - Frees a null-terminated array of strings.
 * @argv: The null-terminated array of strings to be freed.
 *
 */
void free_tokens(char **argv)
{
	if (argv == NULL)
		return;
	free(argv);
}
