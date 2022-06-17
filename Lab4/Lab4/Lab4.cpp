#include <iostream>
#include <random>
#include "MySpace.h"
#include <string>
using namespace std;

bool bracketsCheck(string s)
{
    int x = 0;
    for(char c : s)
    {
        if (c == '(')
            x++;
        else if (c == ')')
        {
            x--;
            if (x < 0)
                return false;
        }
    }
    return x == 0;
}

bool isArifm(char c)
{
    if (c == '+' || c == '-' || c == '/' || c == '*')
        return true;
    return false;
}

bool stringCheck(string s)
{
	for(char c : s)
	{
        if (!isalpha(c) && c != '(' && c != ')' && !isArifm(c))
            return false;
	}
    char prew = '(';
    for(int i = 0; i < s.length(); i++)
    {
        char c = s[i];
        if(prew == '(')
        {
	        if(isArifm(c))
                return false;
            if (c == ')')
                return false;
        }
        else if(prew == ')')
        {
            if (isalpha(c))
                return false;
            if (c == '(')
                return false;
        }
        else if(isalpha(prew))
        {
            if (c == '(')
                return false;
            if (isalpha(c))
                return false;
        }
        else if(isArifm(prew))
        {
            if (c == ')')
                return false;
            if (isArifm(c))
                return false;
        }
        if ((prew == '(' || prew == ')') && (s[i + 1] == '(' || s[i + 1] == ')'))
            return false;
        prew = c;
    }
    return true;
}

string removeSpaces(string s)
{
    string new_s;
	for(char c : s)
	{
        if(c != ' ')
			new_s += c;
	}
    return new_s;
}

bool compareSymbols(char a, char b)
{
    if (a == '(')
    {
        return false;
    }
    else if (b == ')')
        return true;
	else if (a == '+' || a == '-')
    {
        if (b == '+' || b == '-')
            return true;
        return false;
    }
    else if (a == '*' || a == '/')
    {
        if (b == '(' || b == ')')
            return false;
        return true;
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    string s, rez;
    Stack<char> symbols;
    while (true)
    {
		cout << "Введите выражение\n";
        getline(cin, s);
        s = removeSpaces(s);
        if (!bracketsCheck(s) || !stringCheck(s))
        {
            cout << "Выражение записано неверно\n";
        }
        else
            break;
    }
    s = '(' + s + ')';
    symbols.push('(');
    for(int i = 1; i < s.length(); i++)
    {
        char c = s[i];
	    if(isalpha(c))
	    {
            rez += c;
	    }
        else
        {
            
            if(compareSymbols(symbols.top(), c))
            {

                    if (c == ')')
                    {
                        while (symbols.top() != '(')
                        {
                            rez += symbols.top();
                            symbols.pop();
                        }
						symbols.pop();
					}
                    else
                    {
                        while (compareSymbols(symbols.top(), c))
                        {
                            rez += symbols.top();
                            symbols.pop();
                        }
                    }
                    if (c != ')')
                        symbols.push(c);
            }
            else
            {
					symbols.push(c);
            }
        }
    }

    cout << "Обратная польская запись: " << rez << endl;

    Stack <double> values;
    double value;
    for(char c : rez)
    {
	    if(isalpha(c))
	    {
            cout << "Введите " << c << endl;
            double d;
            input(d);
            values.push(d);
	    }
        else
        {
            switch (c)
            {
	            case '+':
	                value = values._top->next_ptr->info + values.top();
	                break;
	            case '-':
	                value = values._top->next_ptr->info - values.top();
	                break;
	            case '*':
	                value = values._top->next_ptr->info * values.top();
	                break;
	            case '/':
                    if(values.top() == 0)
                    {
                        cout << "Ошибка: деление на ноль\n";
                        return 0;
                    }
	                value = values._top->next_ptr->info / values.top();
	                break;
            }
            values.pop();
            values.pop();
            values.push(value);
        }
    }
    cout << "Ответ: " << values.top();
    system("pause");
}

