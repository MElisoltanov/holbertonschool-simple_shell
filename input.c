#include "shell.h"

/**
 * print_prompt - Displays the shell prompt.
 *
 * Return: void
 */
void print_prompt(void)
{
	printf(PROMPT);
	fflush(stdout);
}
/**
 * read_input - Reads a line from the standard input.
 *
 * Return: line
 */
char *read_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t n_chars;

	n_chars = getline(&line, &len, stdin);

	if (n_chars == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[n_chars - 1] == '\n')
	{
		line[n_chars - 1] = '\0';
	}

	return (line);
}

/**
 * is_interactive - Checks if the shell is in interactive mode.
 *
 * Return: 1 if interactive, 0 otherwise.
 */
int is_interactive(void)
{
	return (isatty(STDIN_FILENO));
}
