#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flg_char:  Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flg_char, field_width, precision_hdled, len_size)
{ /* char is stored at left and paddind at buffer's right */
	int i = 0;
	char padd = ' ';

	UNUSED(precision_hdled);
	UNUSED(len_size);

	if (flg_char & F_ZERO)
		pad = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (field_width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < field_width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = pad;

		if (flg_char & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], field_width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], field_width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flg_char:  Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * Return: Number of chars printed.
 */
int write_num(int is_negative, int ind, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	int len = BUFF_SIZE - ind - 1;
	char pad = ' ', extra_char = 0;

	UNUSED(len_size);

	if ((flg_char & F_ZERO) && !(flg_char & F_MINUS))
		pad = '0';
	if (is_negative)
		extra_char = '-';
	else if (flg_char & F_PLUS)
		extra_char = '+';
	else if (flg_char & F_SPACE)
		extra_char = ' ';

	return (write_num(ind, buffer, flg_char, field_width, precision_hdled,
		len, pad, extra_char));
}

/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flg_char:  Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * @len: Number length
 * @pad: Pading char
 * @extra_char: Extra char
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flg_char, int field_width, int precision_hdled,
	int len_size, int len, char pad, char extra_char)
{	int i, padd_start = 1;

	if (precision_hdled == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0'
	&& field_width == 0)
		return (0); /* printf(".0d", 0)  no returned char */
	if (precision_hdled == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
	buffer[ind] = pad = ' ';
	if (precision_hdled > 0 && precision_hdled < len)
		pad = ' ';
	while (precision_hdled > len)
		buffer[--ind] = '0', len++;
	if (extra_char != 0)
		len++;
	if (field_width > len)
	{
		for (i = 1; i < field_width - len + 1; i++)
			buffer[i] = pad;
		buffer[i] = '\0';
		if (flg_char & F_MINUS && pad == ' ')/* extr char Assigned to left of buff */
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[ind], len) + write(1, &buffer[1], i - 1));
		}
		else if (!(flg_char & F_MINUS) && pad == ' ')/* extra char Assigned */
		{
			if (extra_char)
				buffer[--ind] = extra_char;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], len));
		}
		else if (!(flg_char & F_MINUS) && pad == '0')/* extra char to left of padd */
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], len - (1 - padd_start)));
		}
	}
	if (extra_char)
		buffer[--ind] = extra_char;
	return (write(1, &buffer[ind], len));
}
/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of char
 * @flg_char:  Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(len_size);

	if (precision_hdled == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision_hdled > 0 && precision_hdled < length)
		padd = ' ';

	while (precision_hdled > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flg_char & F_ZERO) && !(flg_char && F_MINUS))
		padd = '0';

	if (field_width > length)
	{
		for (i = 0; i < field_width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flg_char & F_MINUS) /* Extra char Assigned to left of buffer */
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @field_width: Wwidth specifier
 * @flg_char: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int field_width, int flg_char, char padd, char extra_c, int padd_start)
{
	int i;

	if (field_width > length)
	{
		for (i = 3; i < field_width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flg_char & F_MINUS && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flg_char & F_MINUS) && padd == ' ')/* extra char to left bufr */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flg_char & F_MINUS) && padd == '0')/* char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

