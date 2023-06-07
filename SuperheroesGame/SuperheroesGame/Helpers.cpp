#include "Helpers.h"
#include <iostream>
bool compareCaseInsensitive(const char* first, const char* second) {
	size_t size = strlen(first);

	if (size != strlen(second))
		return false;

	for (size_t i = 0; i < size; i++)
	{
		if (first[i] != second[i] && abs(first[i] - second[i]) != abs('A' - 'a'))
			return false;
	}
	return true;
}

bool isUpperCase(char ch) {
	return ch >= 'A' && ch <= 'Z';
}
bool isDownCase(char ch) {
	return ch >= 'a' && ch <= 'z';
}
bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}