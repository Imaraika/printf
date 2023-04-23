#include "main.h"

/**
 * get_flg_char - prints the calculated active flags
 * @format: Formatted string in which to print the arguments
 * by Ange and Damascene
 * @i: take a parameter.
 * Return: Flags:
 */

int get_flg_char(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, curied_i;
	int flg_char = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curied_i = *i + 1; format[curied_i] != '\0'; curied_i++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[curied_i] == FLAGS_CH[j])
			{
				flg_char |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = curied_i - 1;

	return (flg_char);
}
