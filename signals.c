#include "shell.h"

/**
 * setup_signals - Install signal handlers required by the shell.
 *
 * Return: void
 */
void setup_signals(void)
{
	signal(SIGINT, sigint_handler);
}

/**
 * sigint_handler - Signal handler for SIGINT (Ctrl+C).
 * @signo: The received signal number (unused).
 *
 * Return: void
 */
void sigint_handler(int signo)
{
	(void)signo;

	write(STDOUT_FILENO, "\n", 1);
}
