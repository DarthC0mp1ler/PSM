#include <iostream>
#include <cmath>
using namespace std;

double deltaTime = 0.05f;
double radius = 2;
double alpha = 0;
double beata = 0;

double g_force = 10;
double mass = 1;
double height = 20;

#define I (2./5.*mass*radius*radius)
#ifndef I
#define I (2./3.*mass*radius*radius)
#endif // !I


double posX = 0;
double posY = radius;

double velocityX = 0;
double angularVelocity = 0;

struct rotator
{
	double first;
	double second;
	double third;
	double fourth;
	
};

struct matrix
{
	double first;
	double second;

	matrix operator*(rotator& r) 
	{
		return matrix
		{
			first * r.first + second * r.second,
			first * r.third + second * r.fourth 
		};
	}

};


ostream& operator<<(ostream& os, const matrix &m)
{
	return os << m.first << "\t" << m.second << endl;
}


double toRad(const double degrees)
{
	return degrees * 3.14159265 / 180;
}


void calcOneStep(matrix &middlePoints, matrix &rotationPoints, rotator &rotator1) 
{
	double s = sin(alpha);
	double acceleration = g_force * s/ (1 + (I /( mass * radius * radius))),
		vel_2 = velocityX + acceleration * deltaTime / 2;
	posX += vel_2 * deltaTime;
	velocityX += acceleration * deltaTime;

	matrix tmp{posX,radius};

	middlePoints = tmp * rotator1;
	middlePoints.second += height;

	double angularAcceleration = acceleration / radius,
		angVel_2 = angularVelocity + angularAcceleration*deltaTime/2;

	beata += angVel_2 * deltaTime;

	angularVelocity += angularAcceleration * deltaTime;

	tmp.first = radius * cos(toRad(90) - beata) + middlePoints.first;
	tmp.second = radius * sin(toRad(90) - beata) + middlePoints.second;

	rotationPoints = tmp;

}

int main() 
{
	alpha = toRad(45);

	matrix m1{0, 0};
	matrix m2{0, 0};

	rotator r1{cos(-alpha),-sin(-alpha),sin(-alpha),cos(-alpha)};
	
	for (size_t i = 0; i < 20; i++)
	{
		calcOneStep(m1,m2,r1);

		cout << "Middle point: " << m1 << "Rotating point: " << m2 << "===============================" << endl;

	}

}