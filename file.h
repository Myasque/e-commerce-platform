#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class file {

public:
	int find_in_file(const char* file_name,string s);//在文件中找寻字符串，返回该字符串的行数，找不到则返回0
	char* read_line_data(const char* file_name, int line_num);//读取指定行数据
	string char_to_str(char* content_char);//字符串转string类型
	void modify_line_data(const char* file_name, int line_num, char* line_data);//修改行数据

};
	
int file::find_in_file(const char* file_name,string s)
{
	
	fstream f(file_name, ios::in | ios::out);
	if (!f)
	{
		cout << "文件打开失败！" << endl;
		return 0;
	}
	string line;
	int num = 1;
	getline(f, line);//从文件中读取一行
	while (f)
	{
		if (line==s)//如果找到了string串
			return num;
		num += 1;//指向下一个账户名
		getline(f, line);
	}
	return 0;
}


char* file::read_line_data(const char* file_name,int line_num)//读取指定行数据
{
	char data[1024] = { 0 };
	ifstream in;
	in.open(file_name);

	int line = 1;
	while (in.getline(data, 1024))
	{
		if (line_num == line)
		{
			break;
		}
		line++;
	}

	in.close();
	return data;
}

string file:: char_to_str(char* content_char)//字符串转string类型
{
	string tempStr;
	for (int i = 0; content_char[i] != '\0'; i++)
	{
		tempStr += content_char[i];
	}
	return tempStr;
}


		

       

void file::modify_line_data(const char* file_name, int line_num, char* line_data)//修改行数据
{
	ifstream in;
	in.open(file_name);

	string strFileData = "";
	int line = 1;
	char tmpline_data[1024] = { 0 };
	while (in.getline(tmpline_data, sizeof(tmpline_data)))
	{
		if (line == line_num)
		{
			strFileData += char_to_str(line_data);
			strFileData += "\n";
		}
		else
		{
			strFileData += char_to_str(tmpline_data);
			strFileData += "\n";
		}
		line++;
	}
	in.close();

	//写入文件
	ofstream out;
	out.open(file_name);
	out.flush();
	out << strFileData;
	out.close();
}



