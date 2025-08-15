#include "shell.h"

/**
 * main - Entry point of the Simple Shell.
 * @argc: Argument count (unused).
 * @argv: Argument vector.
 *
 * Return: 0 on normal termination.
 */
int main(int argc, char **argv)
{
	(void)argc;

	setup_signals();

	return (shell_loop(argv[0]));
}
