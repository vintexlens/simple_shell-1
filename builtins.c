#include "shell.h"

int status;

char *nameOfShell;

/**
 * checkIfCommandInbuilt - checks if a command is a built in
 * @arguements: command and arguments
 *
 * Return: DONT_CREATE_NEW_CHILD_PROCESS if built in, LAUNCH_RUNTIME_PROCESS if not a built in, TERMINATE_PROCESS_EXECUTION if
 * exit shell, EXIT_SHELL_CODE if exiting with a particular code
 */
int checkIfCommandInbuilt(char **arguements)
{
	int i;
	char **arguementsPointer = arguements;

	while (*arguementsPointer != NULL)
	{
		if (**arguementsPointer == '#')
		{
			*arguementsPointer = NULL;
			break;
		}
		*arguementsPointer = checkIfArgumentIsVariable(*arguementsPointer);

		arguementsPointer++;
	}
	if (*arguements == NULL)
		return (DONT_CREATE_NEW_CHILD_PROCESS);

	i = commandAliasProcessing(arguements, NEGATIVE);
	if (i == LAUNCH_RUNTIME_PROCESS || i == DONT_CREATE_NEW_CHILD_PROCESS)
		return (i);

	if (compareString("exit", *arguements, EQUAL) == POSITIVE && arguements[1] != NULL)
	{
		status = stringToInteger(arguements[1]);
		if (status < 0)
		{
			status = 2;
			displayErrorMessage(arguements[0], arguements[1]);
			return (DONT_CREATE_NEW_CHILD_PROCESS);
		}
	}
	if (compareString("exit", *arguements, EQUAL) == POSITIVE)
		return (TERMINATE_PROCESS_EXECUTION);
	else if (compareString("setenv", *arguements, EQUAL) == POSITIVE && arguements[1] != NULL)
		return (configureEnvironmentVariable(arguements[1], arguements[2]));
	else if (compareString("unsetenv", *arguements, EQUAL) == POSITIVE
		 && arguements[1] != NULL)
		return (deleteEnvironmentVariable(arguements[1]));
	else if (compareString("cd", *arguements, EQUAL) == POSITIVE)
		return (changeDirectory(arguements[1]));
	else if (compareString("env", *arguements, EQUAL) == POSITIVE)
		return (displayEnvironMentVariable());

	return (LAUNCH_RUNTIME_PROCESS);
}