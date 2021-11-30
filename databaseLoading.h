#pragma once
#include <mysql.h>
#include <algorithm> // sort()
#include <vector>	 // vector
#include <iostream>
using namespace std;

void finish_with_error(MYSQL* con);

bool compare(int temp, int oxygen);