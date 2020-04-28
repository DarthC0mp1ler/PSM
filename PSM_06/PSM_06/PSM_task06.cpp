#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

#define _LENGTH  3.14159265358979323846  
#define _NO_OF_DIVISIONS 11
#define _deltaX (_LENGTH / (_NO_OF_DIVISIONS-1))
#define deltaTime 0.2
#define iterations 50

#define _SEPARATOR "," // for english excel

#ifndef _SEPARATOR
#define _SEPARATOR ";" // for polish excel
#endif // _SEPARATOR

//#define _OUTPUT_POS  //to output position file uncomment this



double points[_NO_OF_DIVISIONS];
double velocity[_NO_OF_DIVISIONS];
double acceleration[_NO_OF_DIVISIONS];

double points_2[_NO_OF_DIVISIONS];
double velocity_2[_NO_OF_DIVISIONS];
double acceleration_2[_NO_OF_DIVISIONS];

double xs[_NO_OF_DIVISIONS];

void initialize();
void output(ofstream&);
void oneStepCalc();
void outputEnergy(ofstream&, int);

int main()
{
	initialize();
	ofstream file;
#ifdef _OUTPUT_POS
	file.open("outputPosition.txt");
	for (size_t i = 0; i < _NO_OF_DIVISIONS; i++) file << i << _SEPARATOR;
	file << endl;
	output(file);
#else
	file.open("outputEnergy.txt");
	outputEnergy(file,-1);
#endif
	for (size_t i = 0; i < iterations; i++)
	{
		oneStepCalc();
#ifdef _OUTPUT_POS
		output(file);
#else
		outputEnergy(file,i);
#endif
	}
}

void output(ofstream& file)
{
	for (size_t i = 0; i < _NO_OF_DIVISIONS; i++) file << points[i] << _SEPARATOR;
	file << endl;
}

void outputEnergy(ofstream& file,int iter)
{
	iter++;
	double ep = 0.,
		ek = 0.;
	file << iter << _SEPARATOR;
	for (size_t i = 1; i < _NO_OF_DIVISIONS-1; i++)
	{
		ep += pow(points[i-1] - points[i], 2.) / (2 * _deltaX);
		ek += _deltaX * pow(velocity[i], 2.) / 2;
	}
	ep += pow(points[_NO_OF_DIVISIONS - 2] - points[_NO_OF_DIVISIONS - 1], 2.) / (2 * _deltaX);
	file << ep << _SEPARATOR << ek << endl;
}

void middleCalc() 
{
	for (size_t i = 1; i < _NO_OF_DIVISIONS - 1; i++)
	{
		acceleration[i] = (points[i - 1] - 2 * points[i] + points[i + 1]) / pow(_deltaX, 2.); //acceleration
		points_2[i] = points[i] + velocity[i] * deltaTime / 2; // y position in the middle
	}
	for (size_t i = 1; i < _NO_OF_DIVISIONS - 1; i++)
	{
		velocity_2[i] = velocity[i] + acceleration[i] * deltaTime / 2; // velocity in the middle
		acceleration_2[i] = (points_2[i - 1] - 2 * points_2[i] + points_2[i + 1]) / pow(_deltaX, 2.); //acceleration in the middle
	}
}

void initialize()
{
	for (size_t i = 0; i < _NO_OF_DIVISIONS-1; i++)
	{
		xs[i] = i; // x position
		points[i] = sin(i*_deltaX); // y position
	}
	//velocity is 0
	xs[_NO_OF_DIVISIONS - 1] = _NO_OF_DIVISIONS - 1; //x for last position

	middleCalc();
}

void oneStepCalc()
{
	for (size_t i = 0; i < _NO_OF_DIVISIONS - 1; i++)
	{
		points[i] += velocity_2[i]*deltaTime; // y position
		velocity[i] += acceleration_2[i] * deltaTime; // velocity
	}
	middleCalc();
}
