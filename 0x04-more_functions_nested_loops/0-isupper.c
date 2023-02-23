#include "main.h"
/**
 * _isupper - Checks for uppercase character
 *
 * Description: Check character
 * @c: Character
 * Return: Integer
 *
 */
int _isupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}
