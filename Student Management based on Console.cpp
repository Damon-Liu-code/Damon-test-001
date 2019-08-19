#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <windows.h>
#define WIDTH 20
#define space setw(WIDTH)
#define NEWLINE "\r\n"
using namespace std;

void write(const char* filename)
{
	ofstream out;
	out.open(filename, ios::app);
	if (!out.is_open())
	{
		cout << "open error" << endl;
		return;
	}
	else
	{
		int id, age;
		string name;
		cout << "请输入id、姓名、年龄：" << endl;
		cin >> id >> name >> age;
		out.fill(' ');
		out.setf(ios::left);
		out << space << id << space << name << space << age << NEWLINE;
		out.close();
		cout << "添加成功！！" << endl;
	}
}

void read(const char* filename)
{
	ifstream in;
	in.open(filename, ios::in);
	if (!in.is_open())
	{
		cout << "file open error" << endl;
		return;
	}
	else
	{
		stringstream ss;
		char line[100];
		cout.setf(ios::left);
		cout.fill(' ');
		cout << space << "id" << space << "name" << space << "age" << endl;
		while (in.peek() != EOF)
		{
			in.getline(line, 100);
			ss << line;
			int id, age;
			string name;
			ss >> id >> name >> age;
			cout << space << id << space << name << space << age << endl;
			ss.str("");
			ss.clear();
		}
		in.close();
	}
}

void del(const char* filename)
{
	int id;
	cout << "请输入您要删除学生的编号" << endl;
	cin >> id;
	ifstream in;
	in.open(filename, ios::in);
	if (!in.is_open())
	{
		cout << "file open error" << endl;
		return;
	}
	else
	{
		string temp;
		stringstream ss;
		int curId;;
		while (in.peek() != EOF)
		{
			string line;
			getline(in, line);
			ss << line;
			ss >> curId;
			if (curId != id)
			{
				temp += line + NEWLINE;
			}
			ss.str("");
			ss.clear();
		}
		in.close();
		ofstream out;
		out.open(filename, ios::out);
		if (!out.is_open())
		{
			cout << "file open error" << endl;
			return;
		}
		else
		{
			out << temp;
			out.close();
			cout << "删除成功！！" << endl;
		}
	}

}



int search_pos(const char* filename, int id)
{
	ifstream in;
	in.open(filename, ios::in | ios::binary);
	if (!in.is_open())
	{
		cout << "file open error" << endl;
		return -1;
	}
	else
	{
		stringstream ss;
		while (in.peek() != EOF)
		{
			int start = in.tellg();
			string line;
			getline(in, line);
			ss << line;
			int curID;
			ss >> curID;
			if (curID == id)
			{
				in.close();
				return start;
			}
			ss.str("");
		}
		cout << "对不起您查找的同学信息不存在!" << endl;
		in.close();
	}
	return -1;
}

void search(const char* filename)
{
	cout << "请输入您要查找的学生id：" << endl;
	int id;
	cin >> id;
	int pos = search_pos(filename, id);
	string line;
	fstream in;
	in.open(filename, ios::in | ios::binary);
	in.seekg(pos, ios::beg);
	getline(in, line);
	cout.setf(ios::left);
	cout << space << "id" << space << "name" << space << "age" << endl;
	cout << line << endl;
}

void edit(const char* filename)
{
	int id, age;
	string name;
	cout << "请输入您要修改的学生id" << endl;
	cin >> id;
	cout << "请输入该学生新的姓名、年龄" << endl;
	cin >> name >> age;
	stringstream infoTemp;
	infoTemp.fill(' ');
	infoTemp.setf(ios::left);
	infoTemp << space << id << space << name << space << age;
	string newInfo;
	getline(infoTemp, newInfo);
	fstream file;
	file.open(filename, ios::in | ios::out | ios::binary);
	if (!file.is_open())
	{
		cout << "file open error" << endl;
		return;
	}
	else
	{
		int pos = search_pos(filename, id);
		file.seekg(pos, ios::beg);
		file << newInfo;
		cout << "修改后信息为：" << endl;
		cout << newInfo << endl;
		file.close();
	}
}

int main()
{
	const char* filename = "D:\\out.txt";
	while (true)
	{
		cout << "--------------------------" << endl;
		cout << "0、查看全部信息" << endl;
		cout << "1、新增学生信息" << endl;
		cout << "2、删除学生信息" << endl;
		cout << "3、修改学生信息" << endl;
		cout << "4、查找学生信息" << endl;
		int cmd;
		cin >> cmd;
		system("cls");
		switch (cmd)
		{
		case 0:read(filename); break;
		case 1:write(filename); break;
		case 2:del(filename); break;
		case 3:edit(filename); break;
		case 4:search(filename); break;
		}
	}
	return 0;
}
