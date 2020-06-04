#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#define _TotalNo 10000
#define _PI() 3.1415926535897932384626

int main()
{
	vector<float> integrals;
	for (size_t i = 0; i < 1000; i++)
	{
		int count = 0;
		std::srand(std::time(nullptr));
		for (size_t i = 0; i < _TotalNo; i++)
		{
			float x = static_cast<float>(rand()) / (static_cast <float> (RAND_MAX / _PI()));
			float y = static_cast<float>(rand()) / (static_cast <float> (RAND_MAX));
			if (sqrt(y * y) <= sqrt(sin(x) * sin(x))) count++;
		}
		//S_square = PI * 1; S_sin = ?; =>
		//S_sin / S_square = No_inCircle / No_Total; => 
		//S_sin = S_square * No_inCircle / No_Total
		integrals.push_back(_PI() * count/_TotalNo); 
	}
	float avg = 0;
	for (auto in : integrals)
	{
		avg += in;
	}
	avg /= integrals.size();
	cout << "Square is  "<< avg << endl;
}
