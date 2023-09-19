#include "main.h"
/**
* print_unknown - Handles unknown format specifiers.
* @fmt: Formatted string.
* @ind: Index pointer.
*
* Return: Number of characters printed for unknown format.
*/
static int print_unknown(const char *fmt, int *ind)
{
	int unknown_len = 0;

	unknown_len += write(1, "%%", 1);
	if (fmt[*ind - 1] == ' ')
	{
	unknown_len += write(1, " ", 1);
	}
	else
	{
	--(*ind);
	while (fmt[*ind] != ' ' && fmt[*ind] != '%')
	{
	--(*ind);
	}
	if (fmt[*ind] == ' ')
	{
	--(*ind);
	}
	return (1);
	}
	unknown_len += write(1, &fmt[*ind], 1);
	return (unknown_len);
}
/**
* handle_known_formats - Handles known format specifiers.
* @fmt: Formatted string.
* @ind: Index pointer.
* @list: List of arguments.
* @buffer: Buffer array to handle print.
* @flags: Active formatting flags.
* @width: Width specifier.
* @precision: Precision specification.
* @size: Size specifier.
*
* Return: Number of characters printed for known format, or -1 on failure.
*/
static int handle_known_formats(const char *fmt, int *ind, va_list list,
	char buffer[], int flags, int width, int precision, int size)
{
	int i;
	int printed_chars = -1;

	fmt_t fmt_types[] = {
	{'c', print_char}, {'s', print_string}, {'%', print_percent},
	{'i', print_int}, {'d', print_int}, {'b', print_binary},
	{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
	{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
	{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
	{
	if (fmt[*ind] == fmt_types[i].fmt)
	{
	return (fmt_types[i].fn(list, buffer, flags, width, precision, size));
	}
	}
	return (printed_chars);
}
/**
* handle_print - Prints an argument based on its type.
* @fmt: Formatted string in which to print the arguments.
* @ind: Index pointer.
* @list: List of arguments to be printed.
* @buffer: Buffer array to handle print.
* @flags: Active formatting flags.
* @width: Width specifier.
* @precision: Precision specification.
* @size: Size specifier.
*
* Return: Number of characters printed, or -1 on failure.
*/
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	if (fmt[*ind] == '\0')
	{
	return (-1);
	}
	int result = handle_known_formats(

	fmt, ind, list, buffer, flags, width, precision, size
);

	if (result != -1)
	{
	return (result);
	}
	return (print_unknown(fmt, ind));
}
