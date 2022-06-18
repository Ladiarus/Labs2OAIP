#include <iostream>
#include <random>
#include <ctime>
using namespace std;

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
		while(_top != nullptr)
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
		if(_top == nullptr)
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
		if(_top!=nullptr)
		{
			stackData<T>* prew_top = _top;
			_top = _top->next_ptr;
			delete prew_top;
            prew_top = nullptr;
		}
	}
    void outStack()
	{
		stackData<T>* n_top = _top;
		while(n_top!=nullptr)
		{
			cout << n_top->info << endl;
			n_top = n_top->next_ptr;
		}
	}
};
template <typename T>
void input(T& a)
{
    while (true)
    {
        cin >> a;
        if (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ' && cin.peek() != '\t'))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Неверный ввод" << endl;
        }
        else
        {
            return;
        }
    }
}
void input(int& x, int a, int b)
{
    while (true)
    {
        input(x);
        if (x < a || x > b)
        {
            cout <<
                "Неверный ввод\n"
                "Введите число на промежутке от " << a << " до " << b << endl;
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
                "Неверный ввод\n"
                "Введите y или n\n";
        }
        else
        {
            b = (c == 'y' ? true : false);
            return;
        }
    }
}

int main()
{
	srand(time(nullptr));
    setlocale(LC_ALL, "RU");
	Stack<int> stack;
    int n, t;
    bool choice;
    cout << "Введите количество элементов" << endl;
    input(n, 1, 100000);
    cout << "Желаете вводить элементы массива вручную? y/n\n";
    input(choice);
    if (choice)
    {
        for (int i = 0; i < n; i++)
        {
            input(t);
            stack.push(t);
        }
    }
    else
    {
        int random_min, random_max;
        cout << "Введите минимальное случайное значение\n";
        input(random_min);
        cout << "Введите максимальное случайное значение\n";
        input(random_max);
        for (int i = 0; i < n; i++)
        {
            stack.push(rand() % (random_max - random_min + 1) + random_min);
        }
        cout << "Список:\n";
        stack.outStack();
    }
    int sum = 0, avrg;
    stackData<int>* n_top = stack._top;
    while (n_top != nullptr)
    {
        sum += n_top->info;
        n_top = n_top->next_ptr;
    }
    avrg = sum / n;
    cout << "Среднее: " << avrg << endl;
    n_top = stack._top;
    while (n_top != nullptr)
    {
        if (n_top->info % 2 == 0)
            n_top->info = avrg;
    	n_top = n_top->next_ptr;
    }
    cout << "Конечный список:\n";
    stack.outStack();
    system("pause");
}

