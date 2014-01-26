#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>


using namespace std;
const int arrayLength = 100;
const int dataLimit = 100;

static bool
HasMajicIndex (int (&a) [arrayLength], int ilow, int ihigh)
{
	if (ilow > ihigh)	
		return false;

	int imid = (ilow + ihigh)/2;
	if (imid == a [imid])
		return true;

	if (imid < a[imid] && imid < a[ilow])
		return HasMajicIndex (a, imid + 1, ihigh);

	if (imid > a[imid] && imid > a[ihigh])
		return HasMajicIndex (a, ilow, imid - 1);

	bool ret = HasMajicIndex (a, ilow, imid -1);
	if (ret)
		return true;

	ret = HasMajicIndex (a, imid+1, ihigh);

	return ret;
}

int
main ()
{
	int a[arrayLength];

	srand(clock());

	for (int i = 0; i < arrayLength; i++)
	{
		a[i] = rand() % dataLimit;
	}
	
	sort (a, a + 99);

	bool hasMagicIndex = HasMajicIndex (a, 0, 99);
	
	for (int i = 0; i < arrayLength; i++)
		cout << " " <<  a[i];
	cout << endl;

	cout << "Has magic index - " << hasMagicIndex << endl;

	return 0;
}
