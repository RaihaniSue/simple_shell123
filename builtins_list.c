#include "shell.h"
/**
 * builtins_list - entry point
 * @data: data struct
 * Return: the executed functions, -1 otherwise
 **/
int builtins_list(data_of_program *data)
{
	int iterator;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/* in between structure*/
	for (iterator = 0; options[iterator].builtin != NULL; iterator++)
	{
		if (str_compare(options[iterator].builtin, data->command_name, 0))
		{
/*execute the function and return*/
			return (options[iterator].function(data));
		}
/*no match return -1 */
	}
	return (-1);
}
