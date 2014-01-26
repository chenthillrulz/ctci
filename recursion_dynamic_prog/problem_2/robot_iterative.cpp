#include <iostream>
#include <queue>

using namespace std;

struct Coordinates
{
	int x;
	int y;

	Coordinates () : x(0), y(0)
	{
	}

	Coordinates (int iX, int iY):x(iX), y(iY)
	{
	}
};

int 
main (int argc, char *argv[])
{
	int target_x, target_y, count_ways = 0;
	queue<Coordinates> cQueue;

	cout << "Enter the co-ordinates to reach. positive integer and negative integer" << endl;
	cin >> target_x;
	cin >> target_y;

	if (target_x < 0 || target_y > 0) {
		cout << "Invalid arguments " << endl;
		return 0;
	}

	Coordinates begin;
	cQueue.push (begin);

	while (cQueue.empty () == false) {
		Coordinates current = cQueue.front ();
		Coordinates move_right (current.x+1, current.y);
		Coordinates move_down (current.x, current.y-1);

		if (move_right.x <= target_x)
			cQueue.push (move_right);

		if (move_down.y >= target_y)
			cQueue.push (move_down);

		if (current.x == target_x && current.y == target_y)
			count_ways++;

		cQueue.pop ();
	}

	cout << "Number of possible ways to reach - " << count_ways << endl;
	return 0;
}
