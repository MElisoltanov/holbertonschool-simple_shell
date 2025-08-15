#include "shell.h"

/**
 * is_executable - Checks whether a path points to an accessible executable.
 * @path: Path to test
 *
 * Return: 1 if executable, 0 otherwise
 */
int is_executable(const char *path)
{
	struct stat st;

	if (!path)
		return (0);
	if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR))
		return (1);
	return (0);
}

/**
 * join_path - Concatenates a directory and a command into a full path.
 * @dir: Directory (e.g., "/bin")
 * @cmd: Command (e.g., "ls")
 *
 * Return: Allocated string (dir/cmd) to free() after use,
 *         or NULL on error
 */
char *join_path(const char *dir, const char *cmd)
{
	size_t len_dir, len_cmd;
	char *full_path;

	if (!dir || !cmd)
		return (NULL);
	len_dir = strlen(dir);
	len_cmd = strlen(cmd);
	full_path = malloc(len_dir + len_cmd + 2); /* '/' + '\0' */
	if (!full_path)
		return (NULL);
	strcpy(full_path, dir);
	full_path[len_dir] = '/';
	strcpy(full_path + len_dir + 1, cmd);
	return (full_path);
}

/**
 * resolve_path - Searches for the command in the directories listed in PATH
 * @cmd: Command to search for (e.g., "ls")
 *
 * Return: Allocated path (to free) on success, or NULL if not found
 */
char *resolve_path(const char *cmd)
{
	char *path_env, *path_copy, *dir, *full_path;

	if (!cmd || cmd[0] == '\0')
		return (NULL);

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (is_executable(cmd))
			return (strdup(cmd));
		else
			return (NULL);
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	path_copy = strdup(path_env);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		full_path = join_path(dir, cmd);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		if (is_executable(full_path))
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
