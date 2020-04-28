#include <iostream>
#include <cmath>
using namespace std;

float deltaTime = 0.1f;
float radius = 1.f;
float alpha = 0.7854f;
float g_force = -10.f;
float mass = 1;
float omega = 0;

float sumK(const float arr[] ) 
{
	return (arr[0] + 2 * arr[1] + 2 * arr[2] + arr[3])/6;
}

float toRad(const float degrees)
{
	return degrees * 3.14159265 / 180;
}

void oneStepCalc(int lenght)
{
	float e = g_force / radius * sin(alpha),
		tmp_alpha = alpha, 
		tmp_omega = omega;
	float k_omegas[4];
	float k_alphas[4];

	k_omegas[0] = e;
	k_alphas[0] = tmp_omega;
	for (size_t i = 1; i < lenght; i++)
	{
		tmp_alpha += k_alphas[i - 1] * deltaTime / 2;
		tmp_omega += k_omegas[i - 1] * deltaTime / 2;
		e = g_force / radius * sin(tmp_alpha);
		k_alphas[i] = tmp_omega;
		k_omegas[i] = e;
	}



	alpha += sumK(k_alphas) * deltaTime;
	omega += sumK(k_omegas) * deltaTime;
}



int main() 
{
	alpha = 45;
	alpha = toRad(alpha);
	float counter = 0;
	while (counter < 20)
	{
		counter++;
		
		float h = radius * sin(alpha - toRad(90)) + radius, 
			ep = -mass * g_force * h ,
			ek = mass * (omega * omega) * (radius * radius) / 2,
			et = ep + ek;
		cout << "x = " << radius * cos(alpha - toRad(90)) << endl <<
			"y = " << radius * sin(alpha - toRad(90)) << endl <<
			"potential energy = " << ep << endl <<
			"kinetic energy = " << ek << endl <<
			"total energy = " << et << endl;
		oneStepCalc(4);
		cout << "================================" << endl;
		
	}



}

