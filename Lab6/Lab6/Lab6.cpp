#include <iomanip>
#include <iostream>
#include "MySpace.h"

using namespace std;

double calcFunc(double x)
{
    return 0.1 * x * x * x + x * x - 10 * sin(x) - 8;
}

bool findRoot(double e, double prew_x, double& result, int& iterations)
{
    double derivative, func, x;
	for(int k = 1; k <= 100; k++)
	{
        derivative = 3 / 10 * prew_x * prew_x + 2 * prew_x - 10 * cos(prew_x);
        func = calcFunc(prew_x);
        x = prew_x - func / derivative;
        if(x - prew_x < e)
        {
            result =  x;
            iterations = k;
            return true;
        }
        prew_x = x;
	}
    return false;
}

int main()
{
    double h, e = 1e-6, result;
    int a = -4, b = 4, iters;
    setlocale(LC_ALL, "RU");
    cout << "Уравнение: 0.1x^3 + x^2 - 10sin(x) - 8\n";
    cout << "Введите шаг h в интервале [0.000001, 0.4]: ";
    input(h, 0.000001, 0.4);
    cout << "|" << fixed << setw(8) << "Epsilon";
    cout << "|" << fixed << setw(10) << "Root";
    cout << "|" << fixed << setw(10) << "Iterations|\n";
    cout.fill('-');
    cout << setw(32) << '-';
    cout.fill(' ');
    cout << endl;
    bool isFound;
    for(double x = a; x <= b - h; x += h)
    {
        if(calcFunc(x) <= 0 && calcFunc(x+h) > 0 || calcFunc(x) >= 0 && calcFunc(x + h) < 0)
        {
			isFound = findRoot(e, x, result, iters);
	        if(isFound)
	        {
                cout << "|" << fixed << setw(8) << e;
                cout << "|" << fixed << setw(10) << result;
                cout << "|" << fixed << setw(10) << iters;
                cout << "|\n";
	        }
        }
    }
    system("pause");

}

