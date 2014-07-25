#include <iostream>

using namespace std;


static bool
isPallindrome (string &checkStr)
{
	int start = 0, end = checkStr.length() - 1;

	while (start < end)
	{
		if (checkStr[start] != checkStr[end])
			return false;
		++start;--end;
	}

	return true;
}

static bool
substrRecur (string &checkStr)
{
	
}

int 
main (int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Enter a string argument " << endl;
		return -1;
	}

	string pStr(argv[1]);
	bool isPal = isPallindrome (pStr);

	cout << "String is pallindrome - " << isPal << endl;

	return 0;
}
