#include "shell.h"

int status;

char *nameOfShell;

/**
 * and_or - deals with command line logical operators
 * @arguements: command and arguments
 * @operator: first char of logical operator
 * @last_compare: if last command in logic evaluated to POSITIVE or NEGATIVE
 *
 * Return: if this command evaluates to POSITIVE or NEGATIVE
 */
int and_or(char **arguements, char operator, int last_compare)
{
	int i;

	if (last_compare == NONE)
	{
		i = runCommand(arguements);
		if (i == TERMINATE_PROCESS_EXECUTION)
			return (TERMINATE_PROCESS_EXECUTION);
		if (i == POSITIVE)
			return (POSITIVE);

		return (NEGATIVE);
	}
	if (last_compare == POSITIVE && operator == '&')
	{
		i = runCommand(arguements);
		if (i == TERMINATE_PROCESS_EXECUTION)
			return (TERMINATE_PROCESS_EXECUTION);
		if (i == POSITIVE)
			return (POSITIVE);

		return (NEGATIVE);
	}

	if (last_compare == NEGATIVE && operator == '|')
	{
		i = runCommand(arguements);
		if (i == TERMINATE_PROCESS_EXECUTION)
			return (TERMINATE_PROCESS_EXECUTION);
		if (i == POSITIVE)
			return (POSITIVE);

		return (NEGATIVE);
	}

	if (last_compare == POSITIVE && operator == '|')
		return (POSITIVE);

	return (NEGATIVE);
}