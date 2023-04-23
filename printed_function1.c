#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned number
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flg_char: Calculated active flags
 * @field_width: width
 * @precision_hdled: specifies precision
 * @len_size: Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int numbr = va_arg(types, unsigned long int);

	numbr = convert_size_unsgnd(numbr, len_size);

	if (numbr == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (numbr > 0)
	{
		buffer[i--] = (numbr % 10) + '0';
		numbr /= 10;
	}

	i++;
	return (write_unsgnd(0, i, buffer, flg_char, 
				field_width, precision_hdled, len_size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flg_char:  Calculated flags
 * @field_width: width
 * @precision_hdled: specifies precision
 * @len_size: Size specifier
 * Return: Number of chars printed.
 */
int print_octal(va_list types, char buffer[],
	int flg_char, int field_width, int precision_hdled, int len_size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int numbr = va_arg(types, unsigned long int);
	unsigned long int init_numbr = numbr;

	UNUSED(field_width);

	numbr = convert_size_unsgnd(numbr, size);

	if (numbr == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (numbr > 0)
	{
		buffer[i--] = (numbr % 8) + '0';
		numbr /= 8;
	}

	if (flg_char & F_HASH && init_numbr != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flg_char, field__width,
	precision_hdled, len_size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flg_char:  Calculated flags
 * @field_width: width
 * @precision_hdled: specifies precision
 * @len_size: Size specifier
 * Return: Number of chars printed.
 */
int print_hexadecimal(va_list types, char buffer[], 
	int flg_char, int field_width, int precision_hdled, int len_size)
{
	return (print_hexa(types, "0123456789abcdef", buffer, 
	flg_char, 'x',field-width, precision_hdled, len_size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: arguments lists
 * @buffer: Buffer array to handle print
 * @flg_char:  Calculated flags
 * @field_width: width
 * @precision_hdled: specifies precision
 * @len_size: Size specifier
 * Return: Number of chars printed.
 */
int print_hexa_upper(va_list types, char buffer[], 
	int flg_char, int field_width, int precision_hdled, int len_size)
{	return (print_hexa(types, "0123456789ABCDEF", buffer,
	flg_char, 'x',field-width, precision_hdled, len_size));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: arguments lists
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flg_char: Calculated flags
 * @flag_ch: Calculated active flags
 * @field_width: width
 * @precision_hdled: specifies precision
 * @len_size: Size specifier
 * @len_size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flg_char, char flag_ch, int field_width, int precision_hdled, 
	int len_size, int len_size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int numbr = va_arg(types, unsigned long int);
	unsigned long int init_numbr = numbr;

	UNUSED(field_width);

	numbr = convert_size_unsgnd(numbr, len_size);

	if (numbr == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (numbr > 0)
	{
		buffer[i--] = map_to[numbr % 16];
		numbr /= 16;
	}

	if (flg_char & F_HASH && init_numbr != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, 
	flg_char, field_width, precision_hdled, len_size));
}
