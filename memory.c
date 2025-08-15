#include "shell.h"

/**
 * xmalloc - Safe wrapper for malloc
 * @size: Size in bytes to allocate
 *
 * Return: Pointer to allocated memory; exits on failure
 */
void *xmalloc(size_t size)
{
	void *ptr = malloc(size);

	if (!ptr)
	{
		fprintf(stderr, "Erreur: échec malloc(%lu)\n", size);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

/**
 * xrealloc - Safe wrapper for realloc
 * @ptr: Existing pointer to reallocate
 * @size: New size in bytes
 *
 * Return: Reallocated pointer; exits on failure
 */
void *xrealloc(void *ptr, size_t size)
{
	void *new_ptr = realloc(ptr, size);

	if (!new_ptr)
	{
		fprintf(stderr, "Erreur: échec realloc(%lu)\n", size);
		exit(EXIT_FAILURE);
	}
	return (new_ptr);
}

/**
 * free_null_terminated - Frees a NULL-terminated array (e.g., char **argv)
 * @arr: Array to free
 */
void free_null_terminated(char **arr)
{
	int i = 0;

	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
