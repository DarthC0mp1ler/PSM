#include <iostream>
#include <cmath>

//3.14159265358979323846
# define M_PI           3.14159265358979323846
# define M_PI_2         6.28318530717958647692
# define M_3PI_2        4.71238898038468985769
# define ERROR          -123456789

using namespace std;


double factorial(int num) 
{
    if (num == 1) return 1;
    return num * factorial(num - 1);
}

bool includeQuart(double &x) 
{
    if (x < 0) x = -x;
    while(x > M_PI_2)
    {
        x -= M_PI_2;
    }
    if (x >= 0 && x < M_PI / 2.)
    {
        return true;
    }
    else if (x >= M_PI / 2. && x < M_PI)
    {
        x = M_PI - x;
        return true;
    }
    else if (x >= M_PI && x < M_3PI_2)
    {
       x = x - M_PI_2;
        return true;
    }
    else if (x >= M_3PI_2&& x < M_PI_2)
    {
        x = x - M_PI_2;
        return true;
    }
    return false;
}

double mySin(double x) 
{
    if (includeQuart(x)) {
        double res = 0;
        for (int i = 0, j = 1; i < 20; i++, j += 2)
        {
            res += pow(-1, i) * (pow(x, j) / factorial(j));
        }
        return res;
    }
    return ERROR;
}


int main() 
{
    double j;
    cout << "Insert a value: " << endl;
    cin >> j;
    double cmathSin = sin(j);
    double mSin = mySin(j);
    if (mSin == ERROR)
         cout << "ERROR" << endl;
    else
         cout << "sin of " << j << " is: \ncmath answer:" << cmathSin << " in radians;\nmySin answer:" << mSin << " in radians;\nERROR: " << mSin - cmathSin << endl;
     return 0;
}
