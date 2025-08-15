#include "shell.h"

/**
 * print_error - Prints an error to stderr in the format:
 *                prog: line_no: cmd: message
 * @prog: Program name (e.g., "hsh" or argv[0])
 * @line_no: Command line number (incremented at each prompt)
 * @cmd: Faulty command
 * @msg: Error message (e.g., "not found")
 */
void print_error(const char *prog, int line_no,
	const char *cmd, const char *msg)
{
	if (!prog || !cmd || !msg)
		return;

	fprintf(stderr, "%s: %d: %s: %s\n", prog, line_no, cmd, msg);
}

/**
 * perror_cmd - Prints the system error prefixed by the program name
 * @prog: Program name (e.g., "hsh")
 */
void perror_cmd(const char *prog)
{
	if (!prog)
		return;

	perror(prog);
}
