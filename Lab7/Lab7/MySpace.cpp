#include"MySpace.h"

using namespace std;


void input(int& x, int a, int b)
{
    while (true)
    {
        input(x);
        if (x < a || x > b)
        {
            cout <<
                "�������� ����\n"
                "������� ����� �� ���������� �� " << a << " �� " << b << endl;
        }
        else
            return;
    }
}
void input(double& x, double a, double b)
{
    while (true)
    {
        input(x);
        if (x < a || x > b)
        {
            cout <<
                "�������� ����\n"
                "������� ����� �� ���������� �� " << a << " �� " << b << endl;
        }
        else
            return;
    }
}
void input(bool& b)
{
    char c;
    while (true)
    {
        input(c);
        if (c != 'y' && c != 'n')
        {
            cout <<
                "�������� ����\n"
                "������� y ��� n\n";
        }
        else
        {
            b = (c == 'y' ? true : false);
            return;
        }
    }
}