#include <iostream>

#include "MySpace.h"
#include "Tree.h"
using namespace std;

int individualTask_rec(node* p)
{
    if (p == nullptr)
        return 0;
    if (p->left == nullptr && p->right == nullptr)
        return 1;
    return individualTask_rec(p->left) + individualTask_rec(p->right);
}

void individualTask(Tree& tree)
{
    if (tree.root == nullptr)
    {
        std::cout << "Дерево пустое\n";
        return;
    }
    if (tree.root->left == nullptr)
    {
        std::cout << "У дерева нет левой ветви\n";
        return;
    }
	cout<< "Количество листов в левой ветви: " << individualTask_rec(tree.root->left)<<endl;
}

int main()
{
    setlocale(LC_ALL, "RU");
    Tree tree;
    /*for(int i = 1; i <= 15; i++)
    {
		tree.addNode(i, to_string(i));
    }
    tree.show();*/
    int c;
    while (true)
    {
        cout << "1 - Добавить\n2 - Поиск\n3 - Удалить\n4 - Показать\n5 - Обход\n6 - Очистить\n7 - Individual Task\n0 - Выход\n";
        input(c, 0, 7);
        system("cls");
        switch (c)
        {
        case 1:
        {
            cout << "Введите ключ: ";
            int key;
            input(key);
            if (tree.findByKey(key) != nullptr)
            {
                cout << "Ключ уже существует\n";
                system("pause");
                break;
            }
            cout << "Введите модель двери: ";
            string s;
            cin >> s;
            tree.addNode(key, s);
            break;
        }
        case 2:
        {
            cout << "Введите ключ: ";
            int key;
            input(key);
            node* n = tree.findByKey(key);
            if (n == nullptr)
            {
                cout << "Ключа не существует\n";
                system("pause");
                break;
            }
            cout << "Модель: " << n->info<<endl;
            system("pause");
            break;
        }
        case 3:
        {
            cout << "Введите ключ, чтобы удалить: ";
            int key;
            input(key);
            node* n = tree.findByKey(key);
            if (n == nullptr)
            {
                cout << "Ключа не существует\n";
                system("pause");
                break;
            }
            tree.removeByKey(key);
            break;
        }
        case 4:
        {
            tree.show();
            system("pause");
            break;
        }
        case 5:
        {
            if (tree.root == nullptr)
            {
                std::cout << "Дерево пустое\n";
                system("pause");
                break;
            }
            cout << "1 - Left-Root-Right\n2 - Root-Left-Right\n3 - Left-Right-Root\n0 - Выход\n";
            int choise;
            input(choise, 0, 3);
        	switch(choise)
        	{
            case 1:
                tree.printLeftRootRight();
                system("pause");
                break;
            case 2:
                tree.printRootLeftRight();
                system("pause");
                break;
            case 3:
                tree.printLeftRightRoot();
                system("pause");
                break;
            case 0:
                break;
        	}

            break;
        }
        case 6:
        {
            if (tree.root == nullptr)
            {
                std::cout << "Дерево пустое\n";
                system("pause");
                break;
            }
            cout << "Вы действительно хотите очистить дерево? y/n\n";
            bool b;
            input(b);
            if (b)
                tree.clear();
            break;
        }
        case 7:
        {
            individualTask(tree);
            system("pause");
            break;
        }
        case 0:
        {
            return 0;
        }
        }
        system("cls");
    }
}
