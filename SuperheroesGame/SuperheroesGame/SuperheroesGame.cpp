#include <iostream>
#include "System.h"
#include "interface.h"


int main()
{
    System system;

	while (true)
	{
		try
		{
			if (!system.isLogged())
			{
				login(system);
			}
			command(system);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
			continue;
		}
	}
}

