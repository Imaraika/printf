#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flg_char:  Calculated active flags
 * @field_width: Width
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer,
	flg_char, field_width, precision_hdled, len_size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flg_char:  Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	int len = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flg_char);
	UNUSED(field_width);
	UNUSED(precision_hdled);
	UNUSED(len_size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision_hdled >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision_hdled >= 0 && precision_hdled < len)
		len = precision_hdled;

	if (field_width > len)
	{
		if (flg_char & F_MINUS)
		{
			write(1, &str[0], len);
			for (i = field_width - len; i > 0; i--)
				write(1, " ", 1);
			return (field_width);
		}
		else
		{
			for (i = field_width - len; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (field_width);
		}
	}

	return (write(1, str, len));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - percent sign printed
 * by Ange and Damascene
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flg_char: flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flg_char);
	UNUSED(field_width);
	UNUSED(precision_hdled);
	UNUSED(len_size);
	return (write(1, "%%", 1));
}
/**************************PRINT INT *************************/
/**
 * print_char - Prints a char
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flg_char:  Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer,
	flg_char, field__width, precision_hdled, len_size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flg_char:  Calculates active flags
 * @field_width: get width.
 * @precision_hdled: Precision specification
 * @len_size: Size specifier
 * Return: Number of chars printed
 */
int print_binary(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	unsigned int n1, n2, i, sum;
	unsigned int v[32];
	int count;

	UNUSED(buffer);
	UNUSED(flg_char);
	UNUSED(field_width);
	UNUSED(precision_hdled);
	UNUSED(precision_hdled);

	n1 = va_arg(types, unsigned int);
	n2 = 2147483648; /* (2 ^ 31) */
	v[0] = n1 / n2;
	for (i = 1; i < 32; i++)
	{
		n2 /= 2;
		v[i] = (n1 / n2) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += v[i];
		if (sum || i == 31)
		{
			char m = '0' + v[i];

			write(1, &m, 1);
			count++;
		}
	}
	return (count);
}

