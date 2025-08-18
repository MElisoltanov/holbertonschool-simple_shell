#include "shell.h"
/**
 * is_builtin - Checks if the command
 * is a recognized built-in
 * @cmd: command to test
 *
 * Return: 1 if builtin, or 0
 */
int is_builtin(const char *cmd)
{
	if (cmd == NULL || cmd[0] == '\0')
		return (0);

	if (strcmp(cmd, "exit") == 0)
		return (1);

	if (strcmp(cmd, "env") == 0)
		return (1);

	return (0);
}
/**
 * run_builtin - Executes corresponding builtin
 * @argv: arguments (argv[0] = commande)
 * @exit_shell: pointer to shell shutdown flag
 * @exit_status: pointer to exit code
 *
 * Return: 0 if not a builtin, or 1 if executed
 * successfully.
 */
int run_builtin(char **argv, int *exit_shell, int *exit_status)
{
	if (argv == NULL || argv[0] == NULL)
		return (0);

	if (strcmp(argv[0], "exit") == 0)
		return (bi_exit(argv, exit_shell, exit_status));

	else if (strcmp(argv[0], "env") == 0)
		return (bi_env(argv, exit_status));

	return (0);
}
