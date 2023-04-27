#include "shell.h"

int status;

int lineNumber;

char *nameOfShell;

/**
 * displayErrorMessage - display error messages
 * @arg0: the command that caused the error
 * @arg1: the arguement 1 for the command
 */
void displayErrorMessage(char *arg0, char *arg1)
{
	char *err_string_num = _itoa(lineNumber);

	write(STDERR_FILENO, nameOfShell, getStringLength(nameOfShell));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err_string_num, getStringLength(err_string_num));
	free(err_string_num);

	if (compareString("cd", arg0, EQUAL) == POSITIVE)
	{
		status = 2;
		write(STDERR_FILENO, ": cd: Error, can't cd to", 17);
		write(STDERR_FILENO, arg1, getStringLength(arg1));
		write(STDERR_FILENO, "\n", 1);
		return;
	}

	if (compareString("exit", arg0, EQUAL) == POSITIVE)
	{
		write(STDERR_FILENO, ": exit: Not Allowed: ", 24);
		write(STDERR_FILENO, arg1, getStringLength(arg1));
		write(STDERR_FILENO, "\n", 1);
		return;
	}
	if (*arg0 == ';' || *arg0 == '|' || *arg0 == '&')
	{
		status = 2;
		write(STDERR_FILENO, ": Syntax error: \"", 17);
		write(STDERR_FILENO, arg0, 1);
		if (*arg0 == *(arg0 + 1))
			write(STDERR_FILENO, arg0, 1);
		write(STDERR_FILENO, "\" unexpected\n", 14);
		return;
	}

	status = 127;
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, arg0, getStringLength(arg0));
	write(STDERR_FILENO, ": not found\n", 12);
}


/**
 * errorCheckerForInput - checks for unwanted characters
 * @pointer: pointer to segment that should be checked
 * Return: POSITIVE for no error, NEGATIVE for error
 */

int errorCheckerForInput(char *pointer)
{
	char *looper = pointer;

	looper++;
	if (*pointer == ';' && *looper == *pointer)
	{
		displayErrorMessage(pointer, NULL);
		return (NEGATIVE);
	}
	if (*looper == *pointer)
		looper++;

	while (*looper == ' ')
		looper++;

	if (*looper == ';' || *looper == '|' || *looper == '&')
	{
		displayErrorMessage(looper, NULL);
		return (NEGATIVE);
	}

	return (POSITIVE);
}

/**
 * inputCleaner - cleans up command line input
 * @previousBuffer: buffer to be cleaned up
 * @previousSize: the size of the prvious buffer
 *
 * Return: the new, sanitized buffer
 */
char *inputCleaner(char *previousBuffer, size_t *previousSize)
{
	char *currentBuffer = malloc(*previousSize * 3);
	char *newPointer = currentBuffer;
	char *oldPointer = previousBuffer;

	while (*oldPointer != '\0')
	{
		while (*oldPointer == ' ')
			oldPointer++;
		while (*oldPointer	!= ' ' && *oldPointer != ';' && *oldPointer != '|'
		       && *oldPointer != '&' && *oldPointer != '\0')
		{
			*newPointer = *oldPointer;
			newPointer++;
			oldPointer++;
		}
		while (*oldPointer == ' ')
			oldPointer++;
		if (newPointer != currentBuffer && *oldPointer != '\0')
		{
			*newPointer = ' ';
			newPointer++;
		}

		if (*oldPointer == ';' || *oldPointer == '|' || *oldPointer == '&')
		{
			if (errorCheckerForInput(oldPointer) == NEGATIVE)
			{
				*previousSize = 0;
				break;
			}
			*newPointer = *oldPointer;
			if (*oldPointer == ';')
			{
				newPointer++;
				*newPointer = ' ';
			}
			else if (*(oldPointer + 1) == *oldPointer)
			{
				if (newPointer == currentBuffer)
				{
					displayErrorMessage(oldPointer, NULL);
					*previousSize = 0;
					break;
				}
				newPointer++;
				*newPointer = *oldPointer;
				newPointer++;
				*newPointer = ' ';
				oldPointer++;
			}
			newPointer++;
			oldPointer++;
		}
	}
	*newPointer = '\0';
	free(previousBuffer);
	return (currentBuffer);
}