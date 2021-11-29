#include <iostream>
#include <mysql.h>

int main()
{
	std::cout << mysql_get_client_info();

	return 0;
}