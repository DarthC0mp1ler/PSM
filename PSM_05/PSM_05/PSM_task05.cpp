#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

#define _G (6.6743*pow(10,-11))
#define _mSun (1.989*pow(10,30))
#define _mEarth (5.972*pow(10,24))
#define _mMoon (7.347*pow(10,22))
#define _DES (1.5*pow(10,11))
#define _DEM (384400000.)

#define deltaTime (6.*3600.)

#define _SEPARATOR "," // for english excel

#ifndef _SEPARATOR
#define _SEPARATOR ";" // for polish excel
#endif // _SEPARATOR



long double EarthX = 0, EarthY = 0,
MoonX = 0, MoonY = 0,
SunX = 0, SunY = 0;

long double EarthVX = 0, EarthVY = 0,
MoonVX = 0, MoonVY = 0;

void initialize();
void oneStepCalc(long double&, long double&, long double&, long double&, const long double, const long double);


int main()
{
	initialize();
	ofstream file;
	file.open("output.txt");

	file 
		<< to_string(EarthX) << _SEPARATOR << to_string(EarthY)
		<< _SEPARATOR << to_string((MoonX)) << _SEPARATOR << to_string((MoonY)) << endl;
	for (size_t i = 0; i < 5000; i++)
	{
		oneStepCalc(EarthX,EarthY,EarthVX,EarthVY,_mSun,_mEarth);
		oneStepCalc(MoonX, MoonY, MoonVX, MoonVY, _mEarth, _mMoon);
		file 
			<< to_string(EarthX) << _SEPARATOR << to_string(EarthY) 
			<< _SEPARATOR << to_string((MoonX)) << _SEPARATOR << to_string((MoonY)) << endl;
	}
	file.close();

}

void initialize() 
{
	EarthX = SunX;
	EarthY = SunY + _DES;
	MoonX = SunX;
	MoonY = SunY + _DEM;

	EarthVX = sqrt(_G * _mSun / _DES);
	MoonVX = sqrt(_G * _mEarth / _DEM);
}

void oneStepCalc(long double& x, long double& y,long double& vx, long double& vy,const long double M, const long double m)
{
	long double sx_2 = x + vx * deltaTime / 2,
		sy_2 = y + vy * deltaTime / 2;
	{//for x
		
		long double D = sqrt(pow(0. - x, 2.) + pow(0. - y, 2.));
		long double F = _G * M * m / pow(D, 2.);
		long double fx = (0. - x) / D * F;
		long double v_2 = vx + (fx / m) * deltaTime / 2.;
		x += v_2 * deltaTime;

		D = sqrt(pow(0. - sx_2, 2.) + pow(0. - sy_2, 2.));
		F = _G * M * m / pow(D, 2.);
		fx = (0. - sx_2) / D * F;
		
		vx += (fx / m) * deltaTime;

	}
	{//for y
		long double D = sqrt(pow(0. -x, 2.) + pow(0. - y, 2.));
		long double F = _G * M * m / pow(D, 2.);
		long double fy = (0. - y) / D * F;
		long double v_2 = vy + (fy / m) * deltaTime / 2.;
		//cout << (v_2) << endl;
		y += v_2 * deltaTime;

		D = sqrt(pow(0. - sx_2, 2.) + pow(0. - sy_2, 2.));
		F = _G * M * m / pow(D, 2.);
		fy = (0. - sy_2) / D * F;
		vy += (fy / m) * deltaTime;

	}
}