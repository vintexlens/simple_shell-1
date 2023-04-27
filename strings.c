#include "shell.h"

/**
 * compareString - compare strings
 * @firstString: string 1
 * @secondString: string 2
 * @pref_or_match: if prefix or string need to be matched exactly
 * Return: the diffrence of the 2 strings
 */

int compareString(char *firstString, char *secondString, int pref_or_match)
{
	if (firstString == NULL || secondString == NULL)
		return (NEGATIVE);

	while (*firstString != '\0' && *secondString != '\0')
	{
		if (*firstString != *secondString)
			return (NEGATIVE);

		firstString++;
		secondString++;
	}

	if (pref_or_match == PREFIX)
		return (POSITIVE);

	if (*firstString == *secondString)
		return (POSITIVE);

	return (NEGATIVE);
}

/**
 * concatenateString - string concatenation
 * @firstString: string 1
 * @secondString: string 2
 * Return: pointer to new string else NULL
 */
char *concatenateString(char *firstString, char *secondString)
{
	int len = getStringLength(firstString) + getStringLength(secondString);
	char *dest = malloc(len + 1);
	char *pointer = dest;

	if (firstString != NULL)
	{
		while (*firstString != '\0')
		{
			*pointer = *firstString;
			pointer++;
			firstString++;
		}
	}

	if (secondString != NULL)
	{
		while (*secondString != '\0')
		{
			*pointer = *secondString;
			pointer++;
			secondString++;
		}
	}

	*pointer = '\0';

	return (dest);
}

/**
 * copyString - sets aside space in memory for a copy of a string
 * @src: string that makes the copy
 * Return: pointer to copy or NULL
 */

char *copyString(char *src)
{
	int len = getStringLength(src);
	char *dest = malloc(len + 1);
	char *pointer;

	if (dest == NULL)
		exit(EXIT_FAILURE);

	pointer = dest;

	while (*src != '\0')
	{
		*pointer = *src;
		pointer++;
		src++;
	}

	*pointer = '\0';

	return (dest);
}

/**
 *  getStringLength - gets length of a string
 * @string: string to test
 * Return: string length
 */

int getStringLength(char *string)
{
	int i = 0;

	if (string == NULL)
		return (0);

	while (*string != '\0')
	{
		i++;
		string++;
	}

	return (i);
}

/**
 * stringToInteger - change string to number
 * @string: the string
 * Return: the number equivalent
 */
int stringToInteger(char *string)
{
	int n = 0;
	int sign = 1;
	int s_int;

	if (*string == '=' && *(string + 1) >= '0' && *(string + 1) <= '9')
	{
		sign = -1;
		string++;
	}

	while (*string != '\0')
	{
		if (*string >= '0' && *string <= '9')
		{
			s_int = *string - 48;
			if (sign == 1)
				n = (n * 10) + s_int;
			else
				n = (n * 10) - s_int;
		}
		else
			return (-1);
		string++;
	}

	return (n);
}

/**
 * _itoa - string to integer
 * @n: integer to be changed
 * Return: the integer value
 */

char *_itoa(int n)
{
	char *buffer = malloc(12);
	char *pointer = buffer;
	int is_min = NEGATIVE;
	int i_mask = 1000000000;
	int digit = 0;

	if (n == INT_MIN)
	{
		*pointer = '-';
		pointer++;
		n = INT_MAX;
		is_min = POSITIVE;
	}

	if (n < 0)
	{
		*pointer = '-';
		pointer++;
		n = -n;
	}

	while (i_mask > 9 && digit == 0)
	{
		digit = n / i_mask;
		n %= i_mask;
		i_mask /= 10;
	}

	if (digit != 0)
	{
		*pointer = digit + '0';
		pointer++;
	}

	while (i_mask > 9)
	{
		digit = n / i_mask;
		*pointer = digit + '0';
		pointer++;
		n %= i_mask;
		i_mask /= 10;
	}

	if (is_min == POSITIVE)
		n += 1;

	*pointer = n + '0';
	pointer++;
	*pointer = '\0';
	return (buffer);
}
