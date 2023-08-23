#include "mu_shell.h"

/**
 * getlinefunc - custom getline function to read many chars at once
 * Return: linebuf
 */

char *getlinefunc()
{
	int m;
	int start = 0;
	int buf_size = 1;

	char *linebuf = (char *)malloc(buf_size);

	if (!linebuf)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	while ((m = getchar()) != EOF && m != '\n')
	{
		linebuf[start] = m;
		start++;

		if (start >= buf_size)
		{
			buf_size *= 2;
			linebuf = (char *)realloc(linebuf, buf_size);
			if (!linebuf)
			{
				perror("Memory allocarion failed");
				exit(EXIT_FAILURE);
			}
		}
	}
	linebuf[start] = '\0';

	return (linebuf);
}

/**
 * free_args - to free allocated memory
 * @args: character 
 *
 */

void free_args(char **args)
{
	int m;
	for (m = 0; args[m] != NULL; m++)
		{
			free(args[m]);
		}
		free(args);
}
