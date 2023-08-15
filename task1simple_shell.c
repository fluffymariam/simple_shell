#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define USER_INPUT 60

/**
 *
 *
 *
 *
 *
 */

void show_prompt()
{
	printf("enteryourcommand%% ");
	fflush(stdout);
}

int main ()
{
	char input[USER_INPUT];
	char *args[USER_INPUT];
	pid_t pid;

	while (1)
	{
		show_prompt();
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
		break;
		}
	input[strcspn(input, "\n")] = '\0';
	if (strcmp(input, "terminate shell") == 0)
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
		char *args[] = {input, NULL};
		execve(input, args, NULL);
		perror("Execution failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	}

	printf("\n");
	return 0;
}
