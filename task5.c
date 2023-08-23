#include "mu_shell.h"

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

	str_cpy = _strdup(*str);
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
		args[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		args[i] = token;
		token = strtok(NULL, delim);
		i++;
	}
	args[i] = NULL;
	return (args);
}

/**
 * runexec - function to run exec
 * @args: argument vector
 * @env: environment vector
 * @name: name of the shell
 */

void runexec(char **args, char **env, char *name)
{
	pid_t pid;

	pid = fork();
	wait(NULL);
	if (pid == 0)
	{
		execve(args[0], args, env);
		perror(name);
		exit(EXIT_FAILURE);
	}
	else if (pid == -1)
	{
		perror("could not create child process");
	}
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
	char *input = NULL, *path = NULL;
	char **args = NULL, **pathv = NULL;
	size_t i = argc;

	while (1)
	{
		show_prompt();
		path = _getenv(env, "PATH");
		input = getlinefunc();
		if (input == NULL)
			break;
		input[strcspn(input, "\n")] = '\0';
		if (_strcmp(input, "exit") == 0)
			exit(44);
		if (_strcmp(input, "env") == 0)
		{
			for (i = 0; env[i] != NULL; i++)
				print_str(env[i], '\n');
		}
		else
		{
			char *test = NULL;

			args = tokenize(&input, " \n");
			pathv = tokenize(&path, ":");
			check_prog(pathv, args[0], &test);
			if (test == NULL)
				perror(argv[0]);
			else
			{
				args[0] = _strdup(test);
				if (test == NULL)
					perror("file does not exist");
				else
					runexec(args, env, argv[0]);
			}
		}
		/**
		 *
		 * free(input);
		 * free_args(args);
		 * free_args(pathv);
		*/
	}
	return (0);
}
