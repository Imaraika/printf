#include "main.h"

/**
 * get_precision_hdled - prints the Calculated precision
 * @format: Formatted string which printing the arguments
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision_hdled(const char *format, int *i, va_list list)
{
	int curied_i = *i + 1;
	int precision = -1;

	if (format[curied_i] != '.')
		return (precision);

	precision = 0;

	for (curied_i += 1; format[curied_i] != '\0'; curied_i++)
	{
		if (is_digit(format[curied_i]))
		{
			precision *= 10;
			precision += format[curied_i] - '0';
		}
		else if (format[curied] == '*')
		{
			curied_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curied_i - 1;

	return (precision);
}

