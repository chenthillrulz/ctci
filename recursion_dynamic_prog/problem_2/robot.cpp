#include <iostream>

using namespace std;

int
count_steps (int target_x, int target_y, int current_x, int current_y, int **twod)
{
	int count = 0;

	if (twod[current_x][current_y] != -1)
		return twod[current_x] [current_y];

	// Check if a path is blocked
	// if (isBlocked (current_x, current_y))
	// twod[current_x][current_y] = 0;
	// return 0;

	if (current_x != target_x)
		count += count_steps (target_x, target_y, current_x+1, current_y, twod);
	
	if (current_y != target_y)
		count += count_steps (target_x, target_y, current_x, current_y+1, twod);

	if (current_x == target_x && current_y == target_y)
		count++;

	twod[current_x][current_y] = count;

	return count;
}

int
main (int argc, char *argv[])
{
	int x, y, ways_to_reach = 0;

	cout << "Enter the x and y co-ordinates to reach " << endl;
	cin >> x;
	cin >> y;
	
	int two_d_arr [x+1] [y+1];
	int *p [y+1];

	// To avoid this, one could possibly use a $ vector vector< vector <int> > twod_vector;
	// and pass it as a reference to the count_steps function
	for (int i = 0; i < y+1; i++)
		p[i] = two_d_arr[i]; 

	for (int i =0; i < x+1; i++)
		for (int j = 0; j < y+1; j++)
			two_d_arr [i] [j] = -1;

	ways_to_reach = count_steps (x, y, 0, 0, p);

	cout << "Number of ways to reaching using right and down steps  - " << ways_to_reach << endl;

	return 0;
}
