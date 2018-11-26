#pragma once
#include <string>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <cctype>
#include <stack>  
#include <list>
#include <assert.h>
#include <math.h>
#define true 1
#define false 0
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::list;
using std::stack;

struct token
	{
	int line;
	int token_number;
	string key;
	string category;
	//char *key;
	//char *category;
};
