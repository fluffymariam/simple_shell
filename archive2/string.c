#include "mu_shell.h"

/**
 * _strlen - function to count the lenght/ number of characters in a string
 * @str: the string to be counted
 * Return: len upon success
 */

int _strlen(char *str)
{
	int len = 0, m = 0;

	for (m = 0; str[m] != '\0'; m++)
		len++;
	return (len);
}

/**
 * _strdup - this function duplicates the leght of a string
 * @str: string to be duplicated
 * Return: str_cpy
 */

char *_strdup(char *str)
{
	int len = 0, m = 0;
	char *str_cpy = NULL;

	len = _strlen(str);
	str_cpy = malloc(sizeof(char) * (len + 1));

	for (m = 0; str[m] != '\0'; m++)
		str_cpy[m] = str[m];
	str_cpy[m] = '\0';

	return (str_cpy);
}

/**
 * _strcmp - this function compares equal strings
 * @s1: first string to be compared
 * @s2: second string to be compared
 * Return: 0 when success
 */

int _strcmp(char *s1, char *s2)
{
	int len1 = 0, len2 = 0, m = 0, result = 0;

	len1 = _strlen(s1);
	len2 = _strlen(s2);

	if (len1 != len2)
		result = -1;
	else
	{
		for (m = 0; m < len1; m++)
		{
			if (s1[m] != s2[m])
				result = -1;
		}
	}
	return (result);
}
