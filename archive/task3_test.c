#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define USER_INPUT 60

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

/**
 * show_prompt - Function to display initial prompt
 */

void show_prompt(void)
{
	print_str("enteryourcommand% ", '\0');
	fflush(stdout);
}

/**
 * tokenize - function to tokenize a string
 * @str: sting to be tokenized
 * @delim: delimeter
 * Return: and array of tokens
 */
char **tokenize(char **str, char *delim)
{
	char *str_cpy, *token, **args;
	int n = 0, i = 0;

	str_cpy = strdup(*str);
	token = strtok(str_cpy, delim);
	n++;
	while (token)
	{
		token = strtok(NULL, delim);
		n++;
	}
	args = (char **)malloc(sizeof(char *) * (n + 1));
	token = strtok(*str, delim);
	while (token)
	{
		args[i] = malloc(sizeof(char) * (strlen(token) + 1));
		args[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	args[i] = NULL;
	return (args);
}


/**
 * main - Entry point.
 * @argc: number of args
 * @argv: arg vector
 * @env: environment
 * Return: Success
 */
int main(int argc, char *argv[], char **env)
{
	char *input = NULL;
	char **args = NULL;
	size_t n = 0, i = 0;
	pid_t pid = argc;


	while (1)
	{
		show_prompt();
		if (getline(&input, &n, stdin) == -1)
		{
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "exit") == 0)
		{
			exit(44);
		}
		if (strcmp(input, "env") == 0)
		{
			for (i = 0; env[i] != NULL; i++)
			{
				print_str(env[i], '\n');
			}
		}
		else
		{
			args = tokenize(&input, " \n");
			pid = fork();
			if (pid == -1)
			{
				perror("Child process creation failed");
			}
			else if (pid == 0)
			{
				execve(input, args, NULL);
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, NULL, 0);
			}
		}
	}

	return (0);
}
