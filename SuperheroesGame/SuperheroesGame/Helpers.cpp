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