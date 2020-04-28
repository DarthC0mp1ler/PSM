#include <iostream>
using namespace std;


double deltaTime = 0.1f;

void calcNextPosition(double& point, double& velocity, const double& g_force, const double &mass, const double& coefficient)
{
	double acceleration = (mass * g_force - coefficient * velocity) / mass;
	double midVelocity = velocity + acceleration * deltaTime / 2;
	point += midVelocity * deltaTime;
	acceleration = (mass * g_force - coefficient * midVelocity) / mass;
	velocity += acceleration * deltaTime;
}


int main() 
{

	double positionX = 0.,
		positionY = 0.,
		velocityX = 10.,
		velocityY = 10.,
		gX = 0.,
		gY = -10.,
		coeffOfAirRes = 0.4,
		mass = 1.;
	do
	{
		calcNextPosition(positionX, velocityX, gX, mass, coeffOfAirRes);
		calcNextPosition(positionY, velocityY, gY, mass, coeffOfAirRes);


		cout << positionX << "\t"
			<< positionY << "\t" << endl;


	} while (positionY >=0);
}
