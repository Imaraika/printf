#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf a function
 * @format: format produced.
 * Return: char
 */

int _printf(const char *format, ...)
{
	int i, prin = 0, _printchars = 0;
	int flg_char, field__width, precision_hdled, len_size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			_printchars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flg_char = get_flg_char(format, &i);
			field__width = get_field_width(format, &i, list);
			precision_hdled = get_precision_hdled(format, &i, list);
			len_size = get_len_size(format, &i);
			++i;
			prin = handle_print(format, &i, list, buffer,
				flg_char, field__width, precision_hdled, len_size);
			if (prin == -1)
				return (-1);
			_printchars += prin;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (_printchars);
}

/**
 * print_buffer - returns the buffer content if it exists
 * @buffer: Array of charactors
 * @buff_ind: Index at which to add next char, represents the length.
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
