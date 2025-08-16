#include "shell.h"

/**
 * execute_command - Executes a command (builtin or external).
 *
 * @argv: Null-terminated array of command arguments.
 * @exit_shell: Pointer to int that indicates
 * if the shell should exit.
 * @exit_status: Pointer to int that stores
 * the exit status of the command.
 * @prog_name: Name of the shell program (used for error messages).
 * @line_no: Line number of the command (used for error messages).
 *
 * Return: Exit status code of the command.
 *
 */
#include "shell.h"

/**
 * execute_command - Executes a command (builtin or external).
 *
 * @argv: Null-terminated array of command arguments.
 * @exit_shell: Pointer to int that indicates if the shell should exit.
 * @exit_status: Pointer to int that stores the exit status of the command.
 * @prog_name: Name of the shell program (used for error messages).
 * @line_no: Line number of the command (used for error messages).
 *
 * Return: Always 0.
 */
int execute_command(char **argv, int *exit_shell, int *exit_status,
char *prog_name, int line_no)
{
	pid_t pid;
	int status;
	char *path;
	struct stat st;

	if (argv == NULL || argv[0] == NULL)
		return (0);

	if (is_builtin(argv[0]))
	{
		run_builtin(argv, exit_shell, exit_status);
		return (0);
	}
	if (strchr(argv[0], '/') != NULL)
	{
		if (access(argv[0], X_OK) != 0 || stat(argv[0], &st) != 0 || !S_ISREG(st.st_mode))
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line_no, argv[0]);
			*exit_status = 127;
			return (0);
		}
		pid = launch_process(argv[0], argv, environ, &status);
	}
	else
	{
		path = resolve_path(argv[0]);
		if (path == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line_no, argv[0]);
			*exit_status = 127;
			return (0);
		}
		pid = launch_process(path, argv, environ, &status);
		free(path);
	}
	if (pid < 0)
	{
		perror("fork failed");
		*exit_status = 1;
		return (0);
	}
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else
		*exit_status = 1;

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
