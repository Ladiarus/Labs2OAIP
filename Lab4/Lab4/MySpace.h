#pragma once
#include <iostream>

template <typename T>
struct stackData
{
    T info = NULL;
    stackData<T>* next_ptr = nullptr;

};
template <typename T>
class Stack
{
public:
    stackData<T>* _top = nullptr;
    ~Stack()
    {
        while (_top != nullptr)
            pop();
    }
    T top()
    {
        T a = _top->info;
        return a;
    }
    void push(T x)
    {
        stackData<T>* prew_top = _top;
        if (_top == nullptr)
        {
            _top = new stackData<T>();
            _top->info = x;
        }
        else
        {
            _top = new stackData<T>();
            _top->next_ptr = prew_top;
            _top->info = x;
        }
    }
    void pop()
    {
        if (_top != nullptr)
        {
            stackData<T>* prew_top = _top;
            _top = _top->next_ptr;
            delete prew_top;
        }
    }
    void outStack()
    {
        stackData<T>* n_top = _top;
        while (n_top != nullptr)
        {
            std::cout << n_top->info << std::endl;
            n_top = n_top->next_ptr;
        }
    }
};
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
void input(bool& b);