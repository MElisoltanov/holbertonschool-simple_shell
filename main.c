#include "shell.h"

/**
 * main - Entry point of the simple shell.
 *
 * Return: Always 0.
 */
int main(void)
{
	setup_signals();

	return (shell_loop());
}
