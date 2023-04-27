#include "shell.h"

int status;

int line_num;

char *nameOfShell;

/**
 * displayErrorMessage - prints error messages and sets status
 * @arg0: command that is causing error
 * @arg1: first argument to command
 */
void displayErrorMessage(char *arg0, char *arg1)
{
	char *err_string_num = _itoa(line_num);

	write(STDERR_FILENO, nameOfShell, getStringLength(nameOfShell));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err_string_num, getStringLength(err_string_num));
	free(err_string_num);

	if (compareString("cd", arg0, EQUAL) == POSITIVE)
	{
		status = 2;
		write(STDERR_FILENO, ": cd: can't cd to", 17);
		write(STDERR_FILENO, arg1, getStringLength(arg1));
		write(STDERR_FILENO, "\n", 1);
		return;
	}

	if (compareString("exit", arg0, EQUAL) == POSITIVE)
	{
		write(STDERR_FILENO, ": exit: Illegal number: ", 24);
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
 * input_err_check - helper function for sanitizer, check for unexpected char
 * @pointer: pointer to area that needs to be checked
 *
 * Return: POSITIVE if no error, NEGATIVE if error
 */
int input_err_check(char *pointer)
{
	char *iter = pointer;

	iter++;
	if (*pointer == ';' && *iter == *pointer)
	{
		displayErrorMessage(pointer, NULL);
		return (NEGATIVE);
	}
	if (*iter == *pointer)
		iter++;

	while (*iter == ' ')
		iter++;

	if (*iter == ';' || *iter == '|' || *iter == '&')
	{
		displayErrorMessage(iter, NULL);
		return (NEGATIVE);
	}

	return (POSITIVE);
}

/**
 * input_san - sanitizes input from the command line
 * @old_buf: buffer to be sanitized
 * @old_size: size of old buffer
 *
 * Return: the new, sanitized buffer
 */
char *input_san(char *old_buf, size_t *old_size)
{
	char *new_buf = malloc(*old_size * 3);
	char *new_pointer = new_buf;
	char *old_pointer = old_buf;

	while (*old_pointer != '\0')
	{
		while (*old_pointer == ' ')
			old_pointer++;
		while (*old_pointer	!= ' ' && *old_pointer != ';' && *old_pointer != '|'
		       && *old_pointer != '&' && *old_pointer != '\0')
		{
			*new_pointer = *old_pointer;
			new_pointer++;
			old_pointer++;
		}
		while (*old_pointer == ' ')
			old_pointer++;
		if (new_pointer != new_buf && *old_pointer != '\0')
		{
			*new_pointer = ' ';
			new_pointer++;
		}

		if (*old_pointer == ';' || *old_pointer == '|' || *old_pointer == '&')
		{
			if (input_err_check(old_pointer) == NEGATIVE)
			{
				*old_size = 0;
				break;
			}
			*new_pointer = *old_pointer;
			if (*old_pointer == ';')
			{
				new_pointer++;
				*new_pointer = ' ';
			}
			else if (*(old_pointer + 1) == *old_pointer)
			{
				if (new_pointer == new_buf)
				{
					displayErrorMessage(old_pointer, NULL);
					*old_size = 0;
					break;
				}
				new_pointer++;
				*new_pointer = *old_pointer;
				new_pointer++;
				*new_pointer = ' ';
				old_pointer++;
			}
			new_pointer++;
			old_pointer++;
		}
	}
	*new_pointer = '\0';
	free(old_buf);
	return (new_buf);
}