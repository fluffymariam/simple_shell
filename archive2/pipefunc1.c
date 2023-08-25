#include "mu_shell.h"


/**
 * executeCommand - Executes a command with given arguments
 * @args: Command and its arguments
 * @env: Environment variables
 * @pathv: Path variables
 */
void executeCommand(char **args, char **env, char **pathv)
{
	char *full_path;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		full_path = NULL;
		check_prog(pathv, args[0], &full_path);
		if (full_path != NULL)
		{
			execve(full_path, args, env);
			perror(full_path);
			free(full_path);
		}
		else
		{
			perror(args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}


/**
 * pipefunc - Executes a series of piped commands
 * @input: Input commands
 * @env: Environment variables
 * @pathv: Path variables
 */

void pipefunc(char **input, char **env, char **pathv)
{
	int m = 0, fds[2], old_pipe = -1;
	char **args;

	for (m = 0; input[m] != NULL; m++)
	{
		pipe(fds);
		args = tokenize(&input[m], "\n");
		if (args != NULL && args[0] != NULL)
		{
			executeCommand(args, env, pathv);
		}
		if (input[m + 1] != NULL)
		{
			close(fds[1]);
			old_pipe = fds[0];
		}
	}
	close(old_pipe);
	while (wait(NULL) != -1)
	{
	}
}
