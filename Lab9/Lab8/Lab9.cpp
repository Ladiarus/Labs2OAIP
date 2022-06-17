#include "Lab9.h"
#include "LadiarusSpace.h"
int amount_of_lines;
short current_pointer_y;
bool is_exit;
const string INDIVIDUAL_TASK_FILE_NAME = "Individual Task.txt";
const string TEMP_FILE_NAME = "TEMP_FILE_DO_NOT_TOUCH.txt";
COORD curr_coord;
CONSOLE_SCREEN_BUFFER_INFO info;
string curr_in_file, curr_out_file;
const int OUT_WEIGTHS[] = {19, 11, 9, 11, 10};
ifstream fin;
ofstream fout;
fstream finout;
HANDLE hCon;
int binSearch(vector<EmployeeData> &v, double x)
{
    int l = 0, r = v.size() - 1, c;
    while (l < r) 
    {
        c = (l + r) / 2;
        if (x > v[c].workload) 
            l = c + 1;
        else 
            r = c;
    }
    if (abs(v[l].workload - x) < 1e-5)
        return l;
    else 
        return -1;
}

void searchInFileSelect()
{
    double x;
    cout << "Введите объем нагрузки для поиска: ";
    input(x);
    string s;
    fin.close();
    fin.open(curr_in_file);
    amount_of_lines = 0;
    while (!fin.eof())
    {
        getline(fin, s);
        EmployeeData ed = getEmployeeDataByString(s);
        if (abs(ed.workload - x) < 1e-5)
        {
            system("cls");
            cout << centerString("SEARCH_IN_FILE", 65, '-') << "\n"
                "|        Имя        | Факультет | Кафедра | Должность | Нагрузка |\n"
                "|-------------------|-----------|---------|-----------|----------|\n";

            cout << '|' << setw(OUT_WEIGTHS[0]) << ed.name << '|';
            cout << setw(OUT_WEIGTHS[1]) << ed.faculty << '|';
            cout << setw(OUT_WEIGTHS[2]) << ed.department << '|';
            cout << setw(OUT_WEIGTHS[3]) << ed.position << '|';
            cout << setw(OUT_WEIGTHS[4]) << ed.workload << '|' << endl;
            cout << "\033[m";

            system("pause");
            return;
        }

    }
    cout << "Ничего не найдено\n";
    
    system("pause");
}

template <typename T>
void myChooseSort(vector<T>& v, int beg, int end, bool(*comp)(T*, T*))
{
    int i, j, m;
    for (i = beg; i <= end - 1; i++)
    {
        m = i;
        for (j = i + 1; j <= end; j++)
        {
            if (!comp(&v[j], &v[m]))
                m = j;
        }
        swap(v[m], v[i]);
    }
}
template <typename T>
void myQSort(vector<T>& v, int beg, int end, bool(*comp)(T*, T*))
{
    int curr_main_idx = end;
    if (end <= beg)
    {
        
        return;
    }
    int i = beg;
    while (i < curr_main_idx)
    {
        if (comp(&v[i], &v[curr_main_idx]))
        {
            swap(v[i], v[curr_main_idx - 1]);
            swap(v[curr_main_idx - 1], v[curr_main_idx]);
            curr_main_idx--;
        }
        else
        {
            i++;
        }
    }
    myQSort(v, beg, curr_main_idx - 1, comp);
    myQSort(v, curr_main_idx + 1, end, comp);
}

bool intComp(int* a, int* b)
{
    return *a > *b;
}

void movePointer(short y)
{
    SetConsoleCursorPosition(hCon, {0, current_pointer_y});
    cout << ' ';
    current_pointer_y = y;
    SetConsoleCursorPosition(hCon, { 0, y });
    
    cout << "\033[0;32m#\033[0;m";
    SetConsoleCursorPosition(hCon, { 0, y });
    
}
void resetCursor()
{
    SetConsoleCursorPosition(hCon, { 0, current_pointer_y });
    cout << ' ';
    SetConsoleCursorPosition(hCon, { curr_coord });
}

EmployeeData getStudentDataByIdx(int idx)
{
    string s;
    fin.close();
    fin.open(curr_in_file);
    for(int i = 0; i < idx-1; i++)
    {
        fin.ignore(INT_MAX, '\n');
    }
    getline(fin, s);
    return getEmployeeDataByString(s);

}

EmployeeData getEmployeeDataByString(string &s)
{
    EmployeeData sd;
    vector <string> v = splitStr(s, ' ');
    sd.name = v[0] + " " + v[1];
    sd.faculty = v[2];
    sd.department = v[3];
    sd.position = v[4];
    sd.workload = stod(v[5]);
    return sd;
}

bool isNameValid(string s)
{
    vector <string> v = splitStr(s, ' ');
    if (v.size() != 2)
    {
        cout << "\nНеверный ввод, введите через пробел фамилию и инициалы\n";
        return false;
    }
    for (char c : s)
    {
        if (!(isalpha(c) || (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я')) && c != ' ' && c != '.')
        {
            return false;
        }
    }
    if (s.length() > 19)
    {
        cout << "\nМаксимальная длина " << OUT_WEIGTHS[0] << " символов\n";
        return false;

    }
    return true;
}

bool isDoubleValid(string &s, double a, double b)
{
    int num_of_dots = 0;
    if (s[0] == '.')
        s = '0' + s;
    if (s.length() > 15)
        return false;
    for (auto c : s)
        if (c == '.')
            num_of_dots++;

    if (num_of_dots > 1)
        return false;
    double x = stod(s);
    if (x < a || x > b)
        return false;
    return true;
}

bool isIntValid(string s, int a, int b)
{
    if (s.length() > 10)
        return false;
    long long x = stol(s);
    if (x < a || x > b)
        return false;
    return true;
}

void viewOptions()
{
    cout << "1 - Add\n2 - Change\n3 - Delete\n4 - Search\n5 - Sort\n6 - Individual Task\n";
    chooseOption({addStringSelect, editRowSelect, deleteSelect, searchInFileSelect, sortSelect, individualTaskSelect});
}

bool isFileExists(string s)
{
    finout.close();
    finout.open(s, ios::in);
    if (finout.is_open())
    {
        finout.close();
        return true;
    }
    else
    {
        finout.close();
        return false;
    }
}

void viewFile()
{
    system("cls");
    cout << " " << centerString(curr_in_file, 65, '-') << "\n"
        " |        Имя        | Факультет | Кафедра | Должность | Нагрузка |\n"
        " |-------------------|-----------|---------|-----------|----------|\n";
    string s;
    fin.close();
    fin.open(curr_in_file);
    amount_of_lines = 0;
    while (!fin.eof())
    {
        getline(fin, s);
        vector <string>v = splitStr(s, ' ');
        if (v.size() == 6)
        {
            cout << " ";
            if (amount_of_lines % 2 != 0)
            {
                cout << "\033[48;5;235m"; // background color
            }
            cout << "|" << setw(OUT_WEIGTHS[0]) << v[0] + " " + v[1] << "|";

            for (int i = 2; i < v.size(); i++)
            {
                cout << setw(OUT_WEIGTHS[i - 1]) << v[i] << '|';
            }
            cout << ' ' << "\033[34m" << amount_of_lines + 1 << "\033[m" << endl ;
            
        }
        if(!s.empty())  
            amount_of_lines++;
    }
    viewOptions();
}

void createFile(string s)
{
    finout.close();
	finout.open(s, ios::out);
    finout.close();

}

void chooseFileSelect()
{
    string s;
    cout << "Введите название файла, оканчивающееся на .txt\n";
    do {
        input(s, "/<>?|*:\"\\");
        if (s.length() <= 4 || s.substr(s.length() - 4, 4) != ".txt")
            cout << "Неверный ввод\a\n";
    } while (s.length() <= 4 || s.substr(s.length() - 4, 4) != ".txt");
    if (!isFileExists(s))
    {
        bool b;
        cout << "Файла не существует, создать его? y/n\n";
        input(b);
        if (b)
        {
            createFile(s);
        }
    }
    else
    {
		chooseFile(s);
	    
    }
}
void chooseFile(string s)
{
    if (s != INDIVIDUAL_TASK_FILE_NAME)
    {
        fin.close();
        fin.open(s);
        curr_in_file = s;
    }
    else
    {
        cout << "Этот файл нельзя открывать";
    }
}

void editRowSelect()
{
    if (amount_of_lines == 0)
        return;
    int c = 0, y, selected_idx = -1;
    bool isInPointerMode = false;
    cout << "Выберите строку, которую хотите изменить (Стрелка Вверх(Вниз), чтобы переместить указатель)\n";
    cout << "Нажмите ESC, чтобы выйти из режима указателя и ввести номер строки\n";
    GetConsoleScreenBufferInfo(hCon, &info);
    curr_coord = info.dwCursorPosition;


    while (true)
    {
        int c = _getch();
        if (c == 224) { 

            switch (_getch())
        	{
            case KEY_UP:
                y = clamp(current_pointer_y - 1, 3, amount_of_lines + 2);
                movePointer(y);
                break;
            case KEY_DOWN:
                y = clamp(current_pointer_y + 1, 3, amount_of_lines + 2);
                movePointer(y);
                break;
            default:
                ; 
            }
        }
        else if(c == KEY_ENTER) //если нажат Enter
        {
            selected_idx = current_pointer_y - 2;
            resetCursor();
            break;
        }
        else if (c == 27)//если нажат ESC
        {
            resetCursor();
            break;
        }
    }
    if (selected_idx == -1)
    {
        input(selected_idx, 1, amount_of_lines);
    }

    EmployeeData sd = editStudentDataViaGetch(getStudentDataByIdx(selected_idx));
    editRow(selected_idx, sd);
}
void editRow(int idx, EmployeeData sd)
{
    string s;
    fin.close();
    fin.open(curr_in_file);
    createFile(TEMP_FILE_NAME);
    fout.open(TEMP_FILE_NAME);

    for(int i = 0; i < idx-1; i++)
    {
        getline(fin, s);
        fout << s << endl;
    }
    fin.ignore(INT_MAX, '\n');
    fout << sd.name << ' ';
    fout << sd.faculty << ' ';
    fout << sd.department << ' ';
    fout << sd.position << ' ';
    fout << sd.workload;

    while(!fin.eof())
    {
        getline(fin, s);
        fout << "\n" << s;
    }
    fin.close();
    fout.close();
    remove(curr_in_file.c_str());
    rename(TEMP_FILE_NAME.c_str(), curr_in_file.c_str());
}

void sortSelect()
{
    int c, a;
    if (amount_of_lines == 0)
        return;
    vector<EmployeeData> v;
    fin.close();
    fin.open(curr_in_file);
    string s;
    while(!fin.eof())
    {
        getline(fin, s);
        v.push_back(getEmployeeDataByString(s));
    }

    cout << "Имя - 1\nФакультет - 2\nКафедра - 3\nДолжность- 4\nНагрузка - 5\nEXIT - 0\n";
    input(c, 0, 8);
    if (c == 0)
        return;

    cout << "Выберите способ сортировки:\n1 - Быстрая\n2 - Прямого выбора\n";
    int d;
    input(d, 1, 2);

    SortType st;
    switch (d)
    {
    case 1:
        st = SortType::QSort;
        break;
    case 2:
        st = SortType::ChooseSort;
        break;
    }

    switch(c)
    {
    case 1:
        sort(v, st, [](EmployeeData* sd1, EmployeeData* sd2) ->bool
        {
	        return sd1->name > sd2->name;
        });
        break;
    case 2:
        sort(v, st, [](EmployeeData* sd1, EmployeeData* sd2) ->bool
        {
	        return sd1->faculty < sd2->faculty;
        });
        break;
    case 3:
        sort(v, st, [](EmployeeData* sd1, EmployeeData* sd2) ->bool
        {
	        return sd1->department < sd2->department;
        });
        break;
    case 4:
        sort(v, st, [](EmployeeData* sd1, EmployeeData* sd2) ->bool
        {
	        return sd1->position < sd2->position;
        });
        break;
    case 5:
        sort(v, st, [](EmployeeData* sd1, EmployeeData* sd2) ->bool
        {
	        return sd1->workload < sd2->workload;
        });
        break;
    default:;
    }

}

void sort(vector<EmployeeData>& v, SortType st, bool(*comp)(EmployeeData*, EmployeeData*))
{
	switch (st)
	{
    case SortType::QSort:
        myQSort<EmployeeData>(v, 0, v.size() - 1, comp);
        break;
    case SortType::ChooseSort:
        myChooseSort<EmployeeData>(v, 0, v.size() - 1, comp);
        break;
	}
    

    fin.close();
    fout.open(curr_in_file);
    for(int i = 0; i < v.size(); i++)
    {
        EmployeeData sd = v[i];
        fout << sd.name << ' ';
        fout << sd.faculty << ' ';
        fout << sd.department << ' ';
        fout << sd.position << ' ';
        fout << sd.workload;
        if (i < v.size() - 1)
            fout << endl;
    }
    fout.close();

}

void cmdDeleteLeft(int &idx, string &s)
{
    if (idx <= 0)
        return;
    idx = clamp(idx, 1, s.length());
    idx --;
    char c;
    s = s.substr(0, idx) + s.substr(idx + 1, s.length() - idx);
    TO_ROW(s.length() + 1);
	cout<< " "; //в n столбец

    TO_ROW(0);
    cout << s;
    TO_ROW(idx+1);
}
void cmdDeleteRight(int& idx, string& s)
{
    if (idx >= s.length())
        return;
    idx = clamp(idx, 0, s.length()-1);
    char c;
    s = s.substr(0, idx) + s.substr(idx + 1, s.length() - idx);
    TO_ROW(s.length()+1);
    cout << " "; 

    TO_ROW(0);
    cout << s;
   TO_ROW(idx + 1);
}
void cmdAdd(int& idx, string& s, int c)
{
    
    string temp_s = s.substr(0, idx);
    s = temp_s + static_cast<char>(c) + s.substr(idx, s.length() - idx);
    TO_ROW(0);
    cout << s;
    TO_ROW(idx + 2);
    idx++;
}

EmployeeData editStudentDataViaGetch(EmployeeData sd)
{
    cout << "Имя\n";
    cout << sd.name;
    sd.name = editString(sd.name, dataType::String, true);
    CLEAR_LINE();
    UP_LINE();
    CLEAR_LINE();
    TO_ROW(0);
    cout << "Факультет\n";
    cout << sd.faculty;
    sd.faculty = editString(sd.faculty, dataType::String, false);
    CLEAR_LINE();
    UP_LINE();
    CLEAR_LINE();
    TO_ROW(0);
    cout << "Кафедра\n";
    cout << sd.department;
    sd.department = editString(sd.department, dataType::String, false);
    CLEAR_LINE();
    UP_LINE();
    CLEAR_LINE();
    TO_ROW(0);
    cout << "Должность\n";
    cout << sd.position;
    sd.position = editString(sd.position, dataType::String, false);
    CLEAR_LINE();
    UP_LINE();
    CLEAR_LINE();
    TO_ROW(0);
    cout << "Нагрузка\n";
    cout << to_string(sd.workload);
    sd.workload = stod(editString(to_string(sd.workload), dataType::Double, false, 0, 300));
    CLEAR_LINE();
    UP_LINE();
    CLEAR_LINE();
    TO_ROW(0);
    
    return sd;
}
string editString(string curr_s, dataType data_type, bool isName, double min_val, double max_val)
{
    int curr_pos = 0;
    TO_ROW(0);
    while (true)
    {
        bool isA;
        int c = _getch();
        if (c == 224) {

            if(_kbhit()) // если ожидает ввода (не 'а')
            {
                switch (_getch())
                {
                case KEY_LEFT:
                    if (curr_pos > 0)
                    {
                        cout << "\033[1D"; //влево
                        curr_pos--;
                    }
                    break;
                case KEY_RIGHT:
                    if (curr_pos < curr_s.length())
                    {
                        cout << "\033[1C"; //вправо
                        curr_pos++;
                    }
                    break;
                case KEY_DELETE:
                    cmdDeleteRight(curr_pos, curr_s);
                    break;
                }
                continue;
            }
        }
        else if (c == KEY_ENTER)
        {
            if (!curr_s.empty())
            {
                switch (data_type)
                {
                case String:
                    if (isName && isNameValid(curr_s))
                    {
                        return curr_s;
                    }
                    else if (curr_s.length() > 1 && curr_s.find(' ') == string::npos)
                    {
                    	return curr_s;
                    }
                	else
                	{
                        cout << "\nНеверный ввод\n";
                	}
                        
                    break;
                case Double:
                    if (isDoubleValid(curr_s, min_val, max_val))
                        return curr_s;
                    break;
                case Int:
                    if (isIntValid(curr_s, min_val, max_val))
                    {
                        return curr_s;
                    }
                    break;
                }
                TO_ROW(0);
                cout << curr_s;
                TO_ROW(curr_pos + 1);
            }
        	cout << "\a"; // звук
            continue;
        }
        else if (c == KEY_BACKSPACE)
        {
            cmdDeleteLeft(curr_pos, curr_s);
            continue;
        }

        bool is_ok = false;
        int k;
        if('р' < 0 ) k = c - 256; // char почему-то signed ¯\_(ツ)_/¯
        switch (data_type)
        {
        case String:
            if (NAME_INPUT_CHECK)
            {
                is_ok = true;
            }
            break;
        case Double:
            if (DOUBLE_INPUT_CHECK)
            {
                is_ok = true;
            }
            break;
        case Int:
            if (INT_INPUT_CHECK)
            {
                is_ok = true;
            }
            break;
		}
        if(is_ok)
			cmdAdd(curr_pos, curr_s, c);
    }
}

void chooseOption(vector<void(*)()> args)
{
    int choice;
    cout << "EXIT - 0\n";
    input(choice, 0, args.size());
    for (int i = 0; i < args.size(); i++)
    {
        if (i + 1 == choice)
            args[i]();
    }
    if(choice == 0)
    {
        is_exit = true;
    }
    
}

void addStringSelect()
{
    string s;
    vector <string> v;
    EmployeeData *sd = new EmployeeData();
    bool is_valid = false;
    cout << "Введите фамилию и через пробел инициалы\n";
    cin.ignore(1000, '\n');
    while (!is_valid)
    {
	    int sum = 0;
        getline(cin, s);
        is_valid = isNameValid(s);
    }
    sd->name = s;
    cout << "Введите факультет\n";
    getline(cin, s);
    sd->faculty = s;
    cout << "Введите кафедру\n";
    getline(cin, s);
    sd->department = s;
    cout << "Введите должность\n";
    getline(cin, s);
    sd->position = s;
    cout << "Введите объем нагрузки\n";
    input(sd->workload, 0, 300);
    addString(curr_in_file, sd);

}
void addString(string path, const EmployeeData* sd)
{
    fin.close();
    fout.close();
    fout.open(path, ios::app);
    if(amount_of_lines!=0)
		fout << endl;
    fout << sd->name << ' ';
    fout << sd->faculty << ' ';
    fout << sd->department << ' ';
    fout << sd->position << ' ';
    fout << sd->workload;
    fout.close();
    delete sd;
}

void individualTaskSelect()
{
    if (amount_of_lines == 0)
        return;
    string s;

    cout << "Выберите способ сортировки:\n1 - Быстрая\n2 - Прямого выбора\n";
    int c;
    input(c, 1, 2);

    SortType st;
    switch (c)
    {
    case 1:
        st = SortType::QSort;
        break;
    case 2:
        st = SortType::ChooseSort;
        break;
    }

    system("cls");
    cout << centerString("INDIVIDUAL_TASK", 67, '-') << "\n"
        "|        Имя        | Факультет | Кафедра | Должность | Нагрузка |\n"
        "|-------------------|-----------|---------|-----------|----------|\n";
    vector<EmployeeData> v;
    vector<string>departmentsVector;
    fin.close();
    fin.open(curr_in_file);
    while (!fin.eof())
    {
        getline(fin, s);
        v.push_back(getEmployeeDataByString(s));
    }

    sort(v, st, [](EmployeeData* sd1, EmployeeData* sd2) ->bool
        {
            return sd1->workload < sd2->workload;
        });
    for(EmployeeData &ed : v)
    {
	    if(find(departmentsVector.begin(), departmentsVector.end(), ed.department) == departmentsVector.end())
	    {
            departmentsVector.push_back(ed.department);
	    }
    }
    int i = 0;
    for (string s : departmentsVector)
    {
        for (EmployeeData& ed : v)
        {
            if (s == ed.department)
            {
                if (i % 2 != 0)
                {
                    cout << "\033[48;5;235m"; // background color
                }

                cout << '|' << setw(OUT_WEIGTHS[0]) << ed.name << '|';
                cout << setw(OUT_WEIGTHS[1]) << ed.faculty << '|';
                cout << setw(OUT_WEIGTHS[2]) << ed.department << '|';
                cout << setw(OUT_WEIGTHS[3]) << ed.position << '|';
                cout << setw(OUT_WEIGTHS[4]) << ed.workload << '|' <<endl;
	            cout << "\033[m";
	            i++;
            }
        }

    }

    cout << "\033[m" << endl;

    cout << "1 - Бинарный поиск\n0 - EXIT\n";
    input(c, 0, 1);
    if (c == 0)
        return;
    sort(v, st, [](EmployeeData* sd1, EmployeeData* sd2) ->bool
        {
            return sd1->workload > sd2->workload;
        });
    double x;
    cout << "Введите объем нагрузки для поиска: ";
    input(x);
    int f = binSearch(v, x);
    if (f == -1)
    {
        cout << "Ничего не найдено\n";
    }
    else
    {
        system("cls");
        cout << centerString("INDIVIDUAL_TASK", 65, '-') << "\n"
            "|        Имя        | Факультет | Кафедра | Должность | Нагрузка |\n"
            "|-------------------|-----------|---------|-----------|----------|\n";
        EmployeeData& ed = v[f];

        cout << '|' << setw(OUT_WEIGTHS[0]) << ed.name << '|';
        cout << setw(OUT_WEIGTHS[1]) << ed.faculty << '|';
        cout << setw(OUT_WEIGTHS[2]) << ed.department << '|';
        cout << setw(OUT_WEIGTHS[3]) << ed.position << '|';
        cout << setw(OUT_WEIGTHS[4]) << ed.workload << '|' << endl;
        cout << "\033[m";
    }
    system("pause");
    fout.close();

}

void deleteSelect()
{
    fin.close();
    cout << "Введите через пробел номера сотрудников, которых хотите удалить\n";
    string s;
    int a = 0;
    bool isValid;
    cin.ignore();
    getline(cin, s);
    vector<int> linesRaw;
    vector<string> v = splitStr(s, ' ');

    for(string x : v)
    {
        isValid = true;
	    for(int i = 0; i < x.length(); i++)
	    {
		    if(x[i] < '0' || x[i] > '9')
		    {
                cout << "Неверный ввод: " + x + " будет пропущено" << endl;
                isValid = false;
                break;
		    }
	    }
        if(isValid)
        {
            a = stoi(x);
            if(a > amount_of_lines || a < 1)
            {
                cout << "Неверный ввод, выход за пределы: " + x + " будет пропущено" << endl;
            }
            else
            {
                linesRaw.push_back(a);
            }
        }
    }
    if (linesRaw.empty())
        return;
    myQSort<int>(linesRaw, 0, linesRaw.size() - 1, intComp);
    vector<int> lines;
    lines.push_back(linesRaw[0]);
    for(int i = 1; i < linesRaw.size(); i++)
    {
	    if(linesRaw[i] != linesRaw[i - 1])
	    {
            lines.push_back(linesRaw[i]);
	    }
    }
    int arrIdx = 0, fileIdx = 1;
    fin.open(curr_in_file);
    string g, k;
    cout << "Будут удалены:\n";
    while(!fin.eof() && arrIdx < lines.size())
    {
        if (fileIdx == lines[arrIdx])
        {
            fin >> g;
            fin >> k;
            cout << g + " " + k << endl;
            arrIdx++;
        }
        fin.ignore(INT_MAX, '\n');
        fileIdx++;
    }

    bool b;
    cout << "Вы уверены, что хотите удалить эти записи? y/n\n";
    input(b);
    if(b)
		deleteRows(lines);


}

void deleteRows(vector<int>& v)
{
    string s;
    v.push_back(-1); //Ограничитель
    fin.close();
    fin.open(curr_in_file);
    createFile(TEMP_FILE_NAME);
    fout.open(TEMP_FILE_NAME);
    int fileIdx = 1;
    int arrIdx = 0;
    bool is_first_write = true;
    while (!fin.eof())
    {
        if(fileIdx != v[arrIdx])
        {
            getline(fin, s);
            if(!is_first_write) //если не первая строка
            {
                fout << "\n";
            }
        	fout << s;
            is_first_write = false;
        }
        else
        {
            fin.ignore(INT_MAX, '\n');
            arrIdx++;
        }
    	fileIdx++;
    }
    fin.close();
    fout.close();
    remove(curr_in_file.c_str());
    rename(TEMP_FILE_NAME.c_str(), curr_in_file.c_str());
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "en-US"); // устанавливаю locale для цифр и знаков, чтобы работал stod
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    hCon = GetStdHandle(STD_OUTPUT_HANDLE); //Присваивание дескриптора консоли

    COORD  size{ 100, 50 };
    SetConsoleScreenBufferSize(hCon, size);//размер буфера
    
    fin.open("input.txt");
    curr_in_file = "input.txt";
    while (true)
    {
    	viewFile();
        if(is_exit)
            break;
    }
}