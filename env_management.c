#include "shell.h"
/**
 * env_get_key - first entry point
 * @key: variables of env
 * @data: data struct
 * Return: a pointer to value var NULL otherwise
 */
char *env_get_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	/* validation */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/*leng of the variable to be obtained */
	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			return (data->env[i] + key_length + 1);
		}
	}
	/* returns NULL if not found */
	return (NULL);
}

/**
 * env_set_key - second entry point
 * @key: variables of env
 * @value: val new
 * @data: data struct
 * Return: 1 for NULL, 2 for error, 0 for sucess
 */

int env_set_key(char *key, char *value, data_of_program *data)
{
	int i, key_length = 0, is_new_key = 1;

	/* validation*/
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{/* If key already exists */
			is_new_key = 0;
			free(data->env[i]);
			break;
		}
	}
	data->env[i] = str_concat(str_duplicate(key), "=");
	data->env[i] = str_concat(data->env[i], value);

	if (is_new_key)
	{/* if variable new, create at end of list and */
	/* put the NULL value in next position */
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - third entry point
 * @key: removed key
 * @data: data struct
 * Return: 1 for success 0 if key doesnt exist;
 */
int env_remove_key(char *key, data_of_program *data)
{
	int i, key_length = 0;

	/* validation*/
	if (key == NULL || data->env == NULL)
		return (0);

	key_length = str_length(key);

	for (i = 0; data->env[i]; i++)
	{
		if (str_compare(key, data->env[i], key_length) &&
		 data->env[i][key_length] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			/* put NULL value at end of list */
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * print_environ - fourth entry point
 * @data: data struct
 * Return: NULL
 */
void print_environ(data_of_program *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		_print(data->env[j]);
		_print("\n");
	}
}
