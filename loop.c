#include "shell.h"

/**
 * shell_loop - Main loop of the shell that reads input,
 * and executes commands.
 *
 * Return: The exit status of the shell.
 */
int shell_loop(void)
{
	char *line = NULL;
	char **argv = NULL;
	int exit_shell = 0;
	int exit_status = 0;

	while (!exit_shell)
	{
		if (is_interactive())
			print_prompt();

		line = read_input();
		if (line == NULL)
		{
			if (is_interactive())
				write(STDOUT_FILENO, "\n", 1);
			return (exit_status);
		}

		argv = tokenize(line);
		if (argv == NULL || argv[0] == NULL)
		{
			free(line);
			line = NULL;

			if (argv)
			{
				free_tokens(argv);
			}
			argv = NULL;
			continue;
		}
		execute_command(argv, &exit_shell, &exit_status);
		free_tokens(argv);
		argv = NULL;
		free(line);
		line = NULL;
	}
	return (exit_status);
}
