#include "main.h"
/************************* WRITE HANDLE *************************/

/**
* handle_write_char - Print a character with optional formatting.
*
* @c: The character to print.
* @buffer: The buffer to store the output.
* @flags: Flag settings for formatting.
* @width: The width specifier.
* @precision: The precision specifier.
* @size: Size specifier
*
* Return: Number of chars printed.
*/
int handle_write_char(char c, char buffer[], int flags, int width,
	int precision, int size)
{
	int i = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);
	if (flags & F_ZERO)
	padding = '0';
	buffer[i++] = c;
	buffer[i] = '\0';
	if (width > 1)
	{
	buffer[BUFF_SIZE - 1] = '\0';
	for (i = 0; i < width - 1; i++)
	buffer[BUFF_SIZE - i - 2] = padding;
	if (flags & F_MINUS)
	int part1 = write(1, &buffer[0], 1);
	int part2 = write(1, &buffer[BUFF_SIZE - i - 1], width - 1);

	return (part1 + part2);
	else
	int part1 = write(1, &buffer[BUFF_SIZE - i - 1], width - 1);
	int part2 = write(1, &buffer[0], 1);

	return ((part1 + part2));
	}
	return (write(1, &buffer[0], 1));
}
/************************* WRITE NUMBER *************************/

/**
* write_number - Print a number with optional formatting.
*
* @is_negative: Indicates if the number is negative.
* @ind: The index at which the number starts in the buffer.
* @buffer: The buffer to store the output.
* @flags: Flag settings for formatting.
* @width: The width specifier.
* @precision: The precision specifier.
* @size: Size specifier.
*
* Return: Number of chars printed.
*/
int write_number(int is_negative, int ind, char buffer[], int flags,
	int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padding = ' ';
	char extra_char = 0;

	UNUSED(size);
	if ((flags & F_ZERO) && !(flags & F_MINUS))
	padding = '0';
	if (is_negative)
	extra_char = '-';
	else if (flags & F_PLUS)
	extra_char = '+';
	else if (flags & F_SPACE)
	extra_char = ' ';
	int result = write_number_format(

	ind, buffer, flags, width, precision, length, padding, extra_char);
	int formattedLength = result;

	return ((formattedLength));
}
/**
* write_number_format - Format and print a number.
*
* @ind: The index at which the number starts in the buffer.
* @buffer: The buffer to store the output.
* @flags: Flag settings for formatting.
* @width: The width specifier.
* @precision: The precision specifier.
* @length: Number length.
* @padding: Padding character.
* @extra_char: Extra character.
*
* Return: Number of chars printed.
*/
int write_number_format(int ind, char buffer[], int flags, int width,
	int precision, int length, char padding, char extra_char) {
	int i, padding_start = 1;

	bool isSpecialCase = (precision == 0 && ind == BUFF_SIZE - 2 &&
	buffer[ind] == '0' && width == 0);
	if (isSpecialCase)
	return (0);
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
	buffer[ind] = padding = ' ';
	if (precision > 0 && precision < length)
	padding = ' ';
	while (precision > length)
	{
	buffer[--ind] = '0';
	length++;
	}
	if (extra_char != 0)
	length++;
	if (width > length)
	{
	for (i = 1; i < width - length + 1; i++)
	buffer[i] = padding;
	buffer[i] = '\0';
	if (flags & F_MINUS && padding == ' ')
	{
	if (extra_char)
	buffer[--ind] = extra_char;
	return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
	}
	else if (!(flags & F_MINUS) && padding == ' ')
	{
	if (extra_char)
	buffer[--ind] = extra_char;
	return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
	}
	else if (!(flags & F_MINUS) && padding == '0')
	{
	if (extra_char)
	buffer[--padding_start] = extra_char;
	write(1, &buffer[padding_start], i - padding_start);
	return (write(1, &buffer[ind], length - (1 - padding_start)));
	}
	}
	if (extra_char)
	buffer[--ind] = extra_char;
	return (write(1, &buffer[ind], length));
}
