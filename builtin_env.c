#include "shell.h"

/**
 * bi_env - print all environemental variables
 *
 * @argv: array of arguments
 * @exit_status: pointer to output
 *
 * Return: 0
 */
int bi_env(char **argv, int *exit_status)
{
	char **p = environ;

	(void)argv;

	if (exit_status)
		*exit_status = 0;

	if (!p)
		return (0);

	for (; *p; p++)
	{
		size_t len = strlen(*p);

		if (write(STDOUT_FILENO, *p, len) < 0 ||
				write(STDOUT_FILENO, "\n", 1) < 0)
		{
			if (exit_status)
				*exit_status = 1;

			break;
		}
	}

	return (0);
}
