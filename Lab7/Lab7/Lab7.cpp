#include <iostream>
#include <cmath>
#include "MySpace.h";
using namespace std;

double func(double x)
{
    return 0.1*x*x*x + x*x - 10*sin(x);
}

double method(double xt, double* m_x, double* m_y, int m, bool &is_ok)
{
    is_ok = true;
    int i = 2;
    if (xt < m_x[0] || xt > m_x[m - 1])
    {
        is_ok = false;
        return 0;
    }
    while (xt > m_x[i])
        i++;
    i--;
    double n1 = m_y[i - 1] + (xt - m_x[i - 1]) * (m_y[i] - m_y[i - 1]) / (m_x[i] - m_x[i - 1]);
    double n2 = n1 + (xt - m_x[i - 1]) * (xt - m_x[i]) *
	    ((m_y[i - 1] - m_y[i]) / (m_x[i - 1] - m_x[i]) - (m_y[i] - m_y[i + 1]) / (m_x[i] - m_x[i + 1])) / 
        (m_x[i - 1] - m_x[i + 1]);

    return n2;
}

int main()
{
    int a = -4, b = 2, m, n;

    double res1 = 0, res2 = 0;
    setlocale(LC_ALL, "RU");
    cout << "Введите количество узлов [1, 10000]: ";
    input(m, 1, 10000);
    cout << "Введите количество точек аппроксимации [" << m <<", 10000]: ";
    input(n, m, 10000);
    double *m_x = new double[m];
    double *m_y = new double[m];
    double* y_t = new double[n];
    double h = (b - a) / (double)(m-1);
    double h1 = (b - a) / (double)(n-1);

    double x = a;
    for (int i = 0; i < m; i++) 
    {
        m_x[i] = x;
        m_y[i] = func(x);
        x += h;
    }

    x = a;
    double max = 0, f;
    bool is_ok;
    for (int i = 0; i < n; i++, x += h1) 
    {
        y_t[i] = method(x, m_x, m_y, m, is_ok);
        f = func(x);
        if(is_ok)
        {
			cout << "xt = " << x << "  f*(x) = " << y_t[i] << endl;
			if (abs(f - y_t[i]) > max)
			{
			    max = abs(f - y_t[i]);
			}
        }
    }
    cout << "Погрешность: " << max << endl;
    system("pause");
}
