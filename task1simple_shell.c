#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define USER_INPUT 60

/**
 * show_prompt - Function to display initial prompt
 */

void show_prompt(void)
{
	printf("enteryourcommand%% ");
	fflush(stdout);
}
/**
 * main - Entry point.
 * @argc: number of args
 * @argv: arg vector
 * Return: Success
 */
int main(int argc, char *argv[])
{
	char input[USER_INPUT];
	char *args[USER_INPUT];
	pid_t pid = argc;

	while (1)
	{
		show_prompt();
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "exit") == 0)
		{
			break;
		}

		pid = fork();

		if (pid == -1)
		{
			perror("Child process creation failed");
		}
		else if (pid == 0)
		{
			args[0] = input;
			args[1] = NULL;

			execve(input, args, NULL);
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}

	return (0);
}
