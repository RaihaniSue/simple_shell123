#include "shell.h"
/**
 * execute - entry point
 * @data: pointer to data program
 * Return: 0 for success others otherwise
 */
int execute(data_of_program *data)
{
	int retval = 0, status;
	pid_t pidd;

	/* check built ins */
	retval = builtins_list(data);
	if (retval != -1)/* if program found in built ins */
		return (retval);

	/* check program file system */
	retval = find_program(data);
	if (retval)
	{/* if not found */
		return (retval);
	}
	else
	{/* if found */
		pidd = fork(); /* new child process */
		if (pidd == -1)
		{ /* if call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			retval = execve(data->tokens[0], data->tokens, data->env);
			if (retval == -1) /* if error*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
