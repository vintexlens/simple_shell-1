#include "shell.h"

int status;

/**
 * lengthOfList - gets length of a list
 * @list: the list to find length of
 * @entry: the list entry to be indexed
 * Return: length or index if success, -1 if failure
 */
int lengthOfList(char **list, char *entry)
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