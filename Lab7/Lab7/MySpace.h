#pragma once
#include <iostream>

template <typename T>
void input(T& a)
{
    while (true)
    {
        std::cin >> a;
        if (std::cin.fail() || (std::cin.peek() != '\n' && std::cin.peek() != ' ' && std::cin.peek() != '\t'))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Неверный ввод" << std::endl;
        }
        else
        {
            return;
        }
    }
}
void input(int& x, int a, int b);
void input(double& x, double a, double b);
void input(bool& b);