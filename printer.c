#include "mu_shell.h"
/**
 * show_prompt - Function to display initial prompt
 */
void show_prompt(void)
{
	print_str("enteryourcommand% ", '\0');
	fflush(stdout);
}

/**
 * print_str - Function to print strings
 * @str: string o be printed
 * @end: terminator
 */
void print_str(char *str, char end)
{
	char c;
	int i = 0;

	while (str[i])
	{
		c = str[i];
		write(1, &c, 1);
		i++;
	}
	write(1, &end, 1);
}
