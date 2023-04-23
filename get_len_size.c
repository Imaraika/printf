#include "main.h"

/**
 * get_len_size - prints the calculated size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Size specified.
 */

int get_len_size(const char *format, int *i)
{
	int curied_i = *i + 1;
	int len_size = 0;

	if (format[curied_i] == 'l')
		len_size = S_LONG;
	else if (format[curied_i] == 'h')
		len_size = S_SHORT;

	if (len_size == 0)
		*i = curied_i - 1;
	else
		*i = curied_i;

	return (len_size);
}
