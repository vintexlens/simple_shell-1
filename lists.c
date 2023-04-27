#include "shell.h"

int status;

/**
 * list_len - finds the length of a list, or the index of an entry
 * @list: list to be evaluated
 * @entry: entry to be indexed
 *
 * Return: length or index if success, -1 if failure
 */
int list_len(char **list, char *entry)
{
	int i = 0;

	if (entry == NULL)
	{
		while (*list != NULL)
		{
			i++;
			list++;
		}
		i++;
		return (i);
	}
	else
	{
		while (*list != NULL)
		{
			if (compareString(*list, entry, PREFIX) == POSITIVE)
				return (i);

			i++;
			list++;
		}
	}

	return (-1);
}