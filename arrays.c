#include "shell.h"

int status;

/**
 * duplicateArray - copies an array
 * @previousArray: array to be copied
 * @createdArraySize: size of new array
 *
 * Return: the new array
 */
char **duplicateArray(char **previousArray, int createdArraySize)
{
	char **createdArray = NULL;
	char **arrayPointer;

	createdArray = malloc(sizeof(char **) * createdArraySize);

	arrayPointer = createdArray;
	while (*previousArray != NULL)
	{
		*arrayPointer = copyString(*previousArray);
		arrayPointer++;
		previousArray++;
	}
	*arrayPointer = NULL;

	return (createdArray);
}

/**
 * releaseArray - frees a two dimensional array
 * @arguements: array to be freed
 *
 * Return: POSITIVE
 */
int releaseArray(char **arguements)
{
	char **pointer = arguements;

	while (*pointer != NULL)
	{
		free(*pointer);
		pointer++;
	}

	free(arguements);

	return (POSITIVE);
}

/**
 * findArrayElement - gets an element of an array
 * @array: array to be searched
 * @itemName: name of element to be found
 *
 * Return: the array element, or NULL if it is not found
 */
char *findArrayElement(char **array, char *itemName)
{
	while (*array != NULL)
	{
		if (compareString(*array, itemName, PREFIX) == POSITIVE)
			return (*array);

		array++;
	}

	return (NULL);
}

/**
 * createArray - makes a list from a buffer
 * @string: the buffer
 * @endOfListEntryChar: character to mark the end of a list entry
 * @ifSemiColonPointer: if the stringing has semicolons, ifSemiColonPointer becomes the location after the
 * semicolon
 *
 * Return: a pointer to the list
 */
char **createArray(char *string, char endOfListEntryChar, char **ifSemiColonPointer)
{
	char *stringPointer = string;
	unsigned int index = 2;
	char **array = NULL;

	while (*stringPointer != '\0')
	{
		if (*stringPointer == ';')
			break;
		if (*stringPointer == endOfListEntryChar && *(stringPointer + 1) != '\0')
			index++;

		stringPointer++;
	}

	array = malloc(index * sizeof(char **));
	if (array == NULL)
		exit(EXIT_FAILURE);

	array[0] = string;
	stringPointer = string;
	index = 1;

	while (*stringPointer != '\0')
	{
		if (*stringPointer == endOfListEntryChar)
		{
			*stringPointer = '\0';
			stringPointer++;
			if (*stringPointer == ';')
			{
				array[index] = NULL;
				if (*(stringPointer + 1) != '\0' && *(stringPointer + 2) != '\0')
					*ifSemiColonPointer = stringPointer + 2;
				break;
			}
			if (*stringPointer != '\0')
			{
				array[index] = stringPointer;
				index++;
			}
		}
		stringPointer++;
	}
	array[index] = NULL;

	return (array);
}
