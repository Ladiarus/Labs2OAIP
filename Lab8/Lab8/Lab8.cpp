#include <iostream>
#include <cmath>
#include "MySpace.h";
using namespace std;

double func(double x)
{
    return sin(x) * sin(x) - x / 5;
}

double method(int a, int b, int m, double h)
{
    double res = 0;

    for (int i = 2; i <= m; i++)
    {
        res += func(a + (i - 1) * h);
    }

    res += (func(a) + func(b)) / 2;
    res *= h;
    return res;
}

int main()
{
    int a = 0, b = 4, m;
    double e;
    double res1 = 0, res2 = 0;
    setlocale(LC_ALL, "RU");
    cout << "Введите количество разбиений [10, 1e7]: ";
    input(m, 10, 1e7);
    double h = (b - a) / (double)m;
    cout << "Введите максимальную погрешность [0.1, 1e-7]: ";
    input(e, 1e-7, 0.1);
    bool is_first = true;
    res1 = method(a, b, m, h);

    do 
    {
        if(!is_first)
            res1 = res2;
        else
			is_first = false;

        m *= 2;
        h = (b - a) / (double)m;
        res2 = method(a, b, m, h);
    } while (abs(res1 - res2) >= e);

    cout << "Результат: " << res2 << "\nКол-во разбиений: " << m;
    system("pause");
}
