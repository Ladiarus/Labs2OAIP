#pragma once
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_DELETE 83
#define KEY_BACKSPACE 8
#define NAME_INPUT_CHECK (c >= 'a' && c <= 'z' || k >= 'à' && k <= 'ÿ' || c >= 'A' && c <= 'Z' || k >= 'À' && k <= 'ß' || c == ' ')
#define DOUBLE_INPUT_CHECK (c >= '0' && c <= '9' || c == '.')
#define INT_INPUT_CHECK (c >= '0' && c <= '9')
#define TO_ROW(num) (cout<<"\033["+to_string(num)+"G")
#define CLEAR_LINE() (cout<<"\033[2K")
#define UP_LINE() (cout << "\033[1A")

enum dataType
{
	String,
	Double,
	Int
};

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <list>
#include <vector>
#include <Windows.h>
using namespace std;

struct EmployeeData
{
	double workload;
	string name, faculty, department, position;
};

enum class SortType
{
	QSort,
	ChooseSort
};

void moveChar(int x, int y);

void viewOptions();

bool isFileExists(string s);

void viewFile();

void clearFileSelect();

void clearFile(string s);

void createFileSelect();

void createFile(string s);

void chooseFileSelect();

void chooseFile(string s);

void chooseOption(vector<void(*)()> args);

void editRowSelect();

void editRow(int idx, EmployeeData sd);

void sortSelect();

void sort(vector<EmployeeData> &v, SortType st, bool(*comp)(EmployeeData*, EmployeeData*));

void addStringSelect();

void addString(string path, const EmployeeData* sd);

EmployeeData editStudentDataViaGetch(EmployeeData sd);

string editString(string curr_s, dataType data_type, bool isName, double min_val = 0, double max_val = 0);

EmployeeData getStudentDataByIdx(int idx);

EmployeeData getEmployeeDataByString(string &s);

bool isNameValid(string s);

bool isDoubleValid(string s);

bool isIntValid(string s , int a, int b);

void individualTaskSelect();

void deleteSelect();

void deleteRows(vector<int>& v);
