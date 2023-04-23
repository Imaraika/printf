#include "main.h"

/**
 * get_field_width - Prints the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 * by Ange and Damascene
 * Return: The width.
 */

int get_field_width(const char *format, int *i, va_list list)
{
	int curied_i;
	int field_width = 0;

	for (curied_i = *i + 1; format[curied_i] != '\0'; curied_i++)
	{
		if (is_digit(format[curied_i]))
		{
			field_width *= 10;
			field_width += format[curied_i] - '0';
		}
		else if (format[curied_i] == '*')
		{
			curied_i++;
			field_width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curied_i - 1;

	return (field_width);
}
