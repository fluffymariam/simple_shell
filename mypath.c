#include "mu_shell.h"
/**
 * _getenv - function to get environment variable named
 * @env: the enviroment passed
 * @var: the variable key
 * Return: the variable value pair
 */

char *_getenv(char **env, char *var)
{
	int i;
	char *str = NULL;
	char *env_cpy = NULL;
	char **arg = NULL;

	for (i = 0; env[i] != NULL; i++)
	{
		env_cpy = _strdup(env[i]);
		arg = tokenize(&env_cpy, "=");
		if (_strcmp(arg[0], var) == 0)
			str = arg[1];
	}
	return (str);
}
/**
 * check_prog - function to check if program exists
 * @pathv: path vector
 * @progname: program name
 * @result: result
 */
void check_prog(char **pathv, char *progname, char **result)
{
	int i = 0;

	if (access(progname, X_OK) == 0)
		*result = _strdup(progname);
	else
	{
		for (i = 0; pathv[i] != NULL; i++)
		{
			char *test = NULL;

			test = _strdup(pathv[i]);
			strcat(test, "/");
			strcat(test, progname);

			if (access(test, X_OK) == 0)
			{
				*result = _strdup(test);
				break;
			}
		}
	}
}
