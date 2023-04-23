#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flg_char: Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * Return: Number of chars printed
 */
int print_pointer(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	char extra_char = 0, pad = ' ';
	int ind = BUFF_SIZE - 2, len = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addres;
	char map_to[] = "0123456789abcdef";
	void *addres = va_arg(types, void *);

	UNUSED(field_width);
	UNUSED(len_size);

	if (addres == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision_hdled);

	num_addres = (unsigned long)addres;

	while (num_addres > 0)
	{
		buffer[ind--] = map_to[num_addres % 16];
		num_addres /= 16;
		len++;
	}

	if ((flg_char & F_ZERO) && !(flg_char & F_MINUS))
		pad = '0';
	if (flg_char & F_PLUS)
		extra_char = '+', len++;
	else if (flg_char & F_SPACE)
		extra_char = ' ', len++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, len,
		field_width, flg_char, pad, extra_char, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flg_char: Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flg_char);
	UNUSED(field_width);
	UNUSED(precision_hdled);
	UNUSED(len_size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flg_char: Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * Return: Number of chars printed
 */
int print_reverse(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flg_char);
	UNUSED(field_width);
	UNUSED(len_size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision_hdled);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flg_char: Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * Return: Number of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flg_char);
	UNUSED(field_width);
	UNUSED(precision_hdled);
	UNUSED(len_size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}

