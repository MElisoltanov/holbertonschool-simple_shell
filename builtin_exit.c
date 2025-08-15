#include "shell.h"

/**
 * bi_exit - builtin "exit"
 * @argv: arguments array (argv[1] may contain an exit status code)
 * @exit_shell: flag indicating that the shell should terminate
 * @exit_status: exit status to use when leaving the shell
 *
 * Return: 0
 */
int bi_exit(char **argv, int *exit_shell, int *exit_status)
{
	if (argv[1])
		*exit_status = atoi(argv[1]);

	*exit_shell = 1;

	return (0);
}
