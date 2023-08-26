#include "myheader.h"

/**
 * collectinput - this collects input to a buffer
 * @fd: this is the file descriptor to read a file from
 * @buffer: the buffer to get input
 * @bufsize: the size of the buffer
 * Return: number of bytes or -1 if error
 */

ssize_t collectinput(int fd, char *buffer, size_t bufsize)
{
	ssize_t numbytes = read(fd, buffer, bufsize);

	if (numbytes == -1)
	{
		perror("read failed");
		return (-1);
	}
	return (numbytes);
}

/**
 * mygetline - takes a line from the buffer
 * @buffer: the buffer that contains data
 * @position: the curr. position in buff
 * @numbytes: num of bytes in buff
 * @line: the extracted line
 * Return: 1 if line is taken, 0 if not taken
 */

int mygetline(char *buffer, size_t *position, ssize_t numbytes, char **line)
{
	size_t m;
	size_t u;

	if (*position >= numbytes)
		return (0);

	m = *position;
	while (m < numbytes && buffer[m] != '\n')
		m++;
	if (m < numbytes && buffer[m] == '\n')
	{
		u = m - *position + 1;
		*line = (char *) malloc(u);
		if (*line == NULL)
		{
			perror("malloc failed");
			return (-1);
		}
		strncpy(*line, &buffer[*position], u - 1);
		(*line)[u - 1] = '\0';

		*position = m + 1;
		return (1);
	}
	return (0);
}
