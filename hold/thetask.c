#include "myheader.h"

/**
 * execute_command - Executes a command by forking a child process using execlp
 * @command: the command to execute
 */

void execute_command(char *command)
{
	pid_t pid = fork();
	char *args[2];
	char cmd_path[100];

	if (pid == -1)
	{
		perror("fork failed");
		_exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		args[0] = command;
		args[1] = NULL;
		strcpy(cmd_path, "/bin/");
		strcat(cmd_path, command);
		execve(cmd_path, args, NULL);
		perror("execve failed");
		_exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * print_command - this prints the executed command
 * @command: the command to print
 */

void print_command(char *command)
{
	size_t i = 0;

	while (command[i] != '\0')
	{
		write(STDOUT_FILENO, &command[i], 1);
		i++;
	}
	write(STDOUT_FILENO, "\n", 1);
}


/**
 * main - main function of the shell
 * Return: exit status
 */

int main(void)
{
	char input[MAX_INPUT_LENGTH];
	int interactive = isatty(STDIN_FILENO);
	ssize_t bytesRead;

	while (1)
	{
		if (interactive)
		{
			write(STDOUT_FILENO, "($) ", 4);
		}

		bytesRead = read(STDIN_FILENO, input, sizeof(input));
		if (bytesRead == -1)
		{
			perror("read failed");
			_exit(EXIT_FAILURE);
		}
		else if (bytesRead == 0)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			_exit(EXIT_SUCCESS);
		}
		if (input[bytesRead - 1] == '\n')
		{
			input[bytesRead - 1] = '\0';
		}
		if (strcmp(input, "exit") == 0)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			_exit(EXIT_SUCCESS);
		}
		execute_command(input);
		if (!interactive)
			break;
	}
	return (0);
}
