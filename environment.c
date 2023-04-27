#include "shell.h"

int status;

/**
 * displayEnvironMentVariable - prints the environ
 *
 * Return: POSITIVE
 */
int displayEnvironMentVariable(void)
{
	char **pointer = environ;

	while (*pointer != NULL)
	{
		write(STDOUT_FILENO, *pointer, getStringLength(*pointer));
		write(STDOUT_FILENO, "\n", 1);
		pointer++;
	}

	status = 0;

	return (DONT_CREATE_NEW_CHILD_PROCESS);
}

/**
 * configureEnvironmentVariable - sets and environmental variable
 * @name: name of the variable
 * @value: value to set the variable to
 *
 * Return: 0 on success
 */
int configureEnvironmentVariable(const char *name, const char *value)
{
	char **createdEnvironment;
	char *buffer;
	char *buffer_temporary;
	char *element_pointer = findArrayElement(environ, (char *) name);
	int len;

	if (value == NULL)
	{
		write(STDERR_FILENO, "setenv: no value given\n", 23);
		status = 2;
		return (DONT_CREATE_NEW_CHILD_PROCESS);
	}

	buffer = string_concat((char *)name, "=");
	buffer_temporary = string_concat(buffer, (char *)value);
	free(buffer);
	buffer = buffer_temporary;

	if (element_pointer == NULL)
	{
		len = list_len(environ, NULL);
		createdEnvironment = duplicateArray(environ, len + 1);
		createdEnvironment[len - 1] = buffer;
		createdEnvironment[len] = NULL;
		releaseArray(environ);
		environ = createdEnvironment;
		return (DONT_CREATE_NEW_CHILD_PROCESS);
	}

	len = list_len(environ, (char *)name);
	free(environ[len]);
	environ[len] = buffer;

	status = 0;

	return (DONT_CREATE_NEW_CHILD_PROCESS);
}


/**
 * deleteEnvironmentVariable - deletes an environmental variable
 * @name: name of variable
 *
 * Return: 0 if successful
 */
int deleteEnvironmentVariable(const char *name)
{
	char **env_pointer;
	int len = list_len(environ, (char *)name);

	if (len == -1)
	{
		write(STDERR_FILENO, "unsetenv: variable not found\n", 29);
		status = 2;
		return (DONT_CREATE_NEW_CHILD_PROCESS);
	}

	env_pointer = environ + len;
	free(*env_pointer);
	while (*(env_pointer + 1) != NULL)
	{
		*env_pointer = *(env_pointer + 1);
		env_pointer++;
	}
	*env_pointer = NULL;
	status = 0;

	return (DONT_CREATE_NEW_CHILD_PROCESS);
}
