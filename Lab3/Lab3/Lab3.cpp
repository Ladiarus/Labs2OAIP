#include <iostream>
#include <random>
#include <ctime>
using namespace std;

template <typename T>
struct queueData
{
	T info = NULL;
	queueData<T>* next_ptr = nullptr;
    queueData<T>* prew_ptr = nullptr;

};
template <typename T>
class Queue
{
public:
	queueData<T>* _top = nullptr;
    queueData<T>* _end = nullptr;
	~Queue()
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
		if(_top == nullptr)
		{
			_top = new queueData<T>();
			_top->info = x;
            _end = _top;
		}
		else
		{
			queueData<T> * new_elem = new queueData<T>();
            new_elem->info = x;
            new_elem->prew_ptr = _end;
            _end->next_ptr = new_elem;
            _end = new_elem;
		}
	}
    void push_top(T x)
    {
        queueData<T>* prew_top = _top;
        if (_top == nullptr)
        {
            _top = new queueData<T>();
            _top->info = x;
        }
        else
        {

            _top = new queueData<T>();
            _top->next_ptr = prew_top;
            _top->info = x;
            prew_top->prew_ptr = _top;
        }
    }
	void pop()
	{
		if(_top!=nullptr)
		{
			queueData<T>* prew_top = _top;
			_top = _top->next_ptr;
            _top->prew_ptr = nullptr;
			delete prew_top;
		}		
	}
    void outQueue()
	{
		queueData<T>* n_top = _top;
		while(n_top!=nullptr)
		{
			cout << n_top->info << endl;
			n_top = n_top->next_ptr;
		}
	}
    void outQueueBack()
    {
        queueData<T>* n_end = _end;
        while (n_end != nullptr)
        {
            cout << n_end->info << endl;
            n_end = n_end->prew_ptr;
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
	Queue<int> queue;
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
            queue.push(t);
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
            queue.push(rand() % (random_max - random_min + 1) + random_min);
        }
        cout << "Список:\n";
        queue.outQueue();
    }

    int sum = 0, avrg;
    queueData<int>* n_top = queue._top;
    while (n_top != nullptr)
    {
        sum += n_top->info;
        n_top = n_top->next_ptr;
    }
    avrg = sum / n;
    cout << "Среднее: " << avrg << endl;
    n_top = queue._top;
    while (n_top != nullptr)
    {
        if (n_top->info % 2 == 0)
            n_top->info = avrg;
        n_top = n_top->next_ptr;
    }
    cout << "Конечный список:\n";
    queue.outQueue();
    system("pause");
}

