#include "shell.h"
/**
 * get_exec_path - Determines the full path for a command.
 * @cmd: The command name.
 *
 * Return: The allocated full path, or NULL on error.
 */
char *get_exec_path(char *cmd)
{
	if (strchr(cmd, '/') != NULL)
	{
		if (is_executable(cmd))
			return (strdup(cmd));
		else
			return (NULL);
	}
	else
	{
		return (resolve_path(cmd));
	}
}
/**
 * execute_command - Executes a command (builtin or external).
 *
 * @argv: Null-terminated array of command arguments.
 * @exit_shell: Pointer to shell exit flag.
 * @exit_status: Pointer to command exit status.
 * @prog_name: Name of the shell program.
 * @line_no: Line number in the input script (for error reporting).
 *
 * Return: 0 on success.
 */
int execute_command(char **argv, int *exit_shell, int *exit_status,
char *prog_name, int line_no)
{
	char *path;

	if (is_builtin(argv[0]))
	{
		run_builtin(argv, exit_shell, exit_status);
		return (0);
	}
	path = get_exec_path(argv[0]);
	if (path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, line_no, argv[0]);
		*exit_status = 127;
		return (0);
	}
	launch_process(path, argv, environ, exit_status);
	if (strchr(argv[0], '/') == NULL)
	{
		free(path);
	}
	return (0);
}
/**
 * launch_process - Creates a child process to run an external command.
 *
 * @path: Path to the executable file.
 * @argv: Null-terminated array of arguments.
 * @envp: Environment variables.
 * @status: Pointer to an int to store the exit status.
 *
 * Return: PID of the created child process.
 */
pid_t launch_process(const char *path, char **argv, char **envp, int *status)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		*status = 1;
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(path, argv, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		if (waitpid(pid, status, 0) == -1)
		{
			perror("waitpid");
			*status = 1;
			return (-1);
		}
	}
	return (pid);
}
