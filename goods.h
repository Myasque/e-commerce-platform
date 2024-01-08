
#define FOOD 1
#define CLOTHES 2
#define BOOK 3

#include<cstdio>
#include<iostream>
#include<cstring>
#include<fstream>
#include"file.h"

using namespace std;

class goods {
public:
	string name;
	string seller;//此商品所属商家
	float price;
	int type;
	int left;
	

	virtual float get_price() = 0;
	virtual int get_type() = 0;
	void add(string belong);//添加商品
	void show() const;//展示商品
	void search() const ;//寻找商品
	void discount(float n,int type);//打折活动
	void change_left();//更改剩余量
	void change_price();//更改价格


};

class food :public goods {
	
public:
	float get_price() { return price; };//得到价格
	int get_type() { return FOOD; };//得到类型
};

class clothes :public goods {
public:
	float get_price() { return price; };
	int get_type() { return CLOTHES; };
};

class book :public goods {
public:
	float get_price() { return price; };
	int get_type() { return BOOK; };
};


void goods::add(string belong)
{
	fstream iofile("goods.txt", ios::app);
	string name_in;
	float price_in;
	int left_in;
	cout << "请输入新添加商品名称：" << endl;
	cin >> name_in;
	iofile << name_in << endl;

	iofile << belong << endl;//写入所属商家账号

	cout << "请输入新添加商品价格：" << endl;
	cin >> price_in;
	iofile << price_in << endl;

	iofile << get_type() << endl;//写入类型

	cout << "请输入新添加商品剩余量：（正整数）" << endl;
	cin >> left_in;
	iofile << left_in << endl;
	cout << "该商品已成功添加！" << endl;
	iofile.close();
}


void goods::show() const
{
	int n = 1;
	string s;
	int type;
	int left;
	fstream iofile("goods.txt", ios::in | ios::out);
	getline(iofile, s);
	while (!s.empty())
	{
		cout << "商品" << n << endl;//序号

		cout << "名称：" << s << endl;
		getline(iofile, s);
		cout << "所属商家：" << s << endl;
		getline(iofile, s);
		cout << "价格：" << s << "元"<<endl;
		getline(iofile, s);
		type = stoi(s);
		switch (type)
		{
			case FOOD: cout << "类型：食物" << endl; break;
			case CLOTHES: cout << "类型：衣物" << endl; break;
			case BOOK:cout << "类型：书籍" << endl;
		}
		getline(iofile, s);
		left = stoi(s);
		cout << "剩余量：" << left << endl;
		cout << "\n\n";
		n++;
		getline(iofile, s);

	}
	
	iofile.close();
}

void goods::change_left()
{
	string name_in;
	char left_in[10] = {0};
	int line_n;
	file f;
	fstream iofile("goods.txt", ios::in | ios::app);
	cout << "请输入要更改的商品名称" << endl;
	cin >> name_in;
	cout << "请输入更改后的剩余量：" << endl;
	cin >> left_in;
	line_n=f.find_in_file("goods.txt", name_in);//根据商品名称找到 所在的行数
	line_n += 4;//剩余量所在行
	f.modify_line_data("goods.txt", line_n, left_in);//更改left
}

void goods:: change_price()
{
	string name_in;
	char price_in[10] = {10};
	int line_n;
	file f;
	fstream iofile("goods.txt", ios::in | ios::app);
	cout << "请输入要更改的商品名称" << endl;
	cin >> name_in;
	cout << "请输入更改后的价格：" << endl;
	cin >> price_in;
	
	line_n = f.find_in_file("goods.txt", name_in);//根据商品名称找到 所在的行数
	line_n += 2;//剩余量所在行
	f.modify_line_data("goods.txt", line_n, price_in);//更改left
}


void goods::search() const
{
	//依据名称对商品进行搜索
	string name_in;
	file f;
	int line_n;
	fstream iofile("goods.txt", ios::in | ios::out);
	char belong_file[10] = { 0 };
	char price_file[10] = { 0 };
	char type_file[10] = { 0 };
	char left_file[10] = { 0 };
	char temp[10] = { 0 };
	cout << "请输入要搜索的商品名称：" << endl;
	cin >> name_in;
	line_n=f.find_in_file("goods.txt", name_in);
	while (line_n == 0)
	{
		cout << "未找到此商品，请重新输入名称：" << endl;
		cin >> name_in;
		line_n = f.find_in_file("goods.txt", name_in);
	}
	strcpy_s(belong_file, f.read_line_data("goods.txt", line_n + 1));
	strcpy_s(price_file,f.read_line_data("goods.txt",line_n + 2));
	strcpy_s(type_file, f.read_line_data("goods.txt", line_n + 3));
	strcpy_s(left_file, f.read_line_data("goods.txt", line_n + 4));
	
	cout << "名称：" << name_in << endl;
	cout << "所属商家：" << belong_file << endl;
	cout << "价格：" << price_file << endl;
	if(!strcmp(type_file,"1")) cout<<"类型：食品"<<endl;
	if(!strcmp(type_file, "2")) cout << "类型：衣物" << endl;
	if(!strcmp(type_file, "2")) cout << "类型：书籍" << endl;
	cout << "剩余量：" << left_file << endl;
	iofile.close();
}

void goods:: discount(float n,int type)
{
	//int type = 0;
	int n_line = 0;
	char temp[10];

	string s;
	file f;
	float money;
	
	while (type !=FOOD && type != CLOTHES && type != BOOK) { cout << "输入非法，请重新输入：" << endl; cin >> type;}
	s = to_string(type);
	n_line = f.find_in_file("goods.txt", s);
	n_line--;//指向价格行
	strcpy_s(temp, f.read_line_data("goods.txt", n_line));
	s = f.char_to_str(temp);
	money = stof(s);
	money = money * n;//打折
	s = to_string(money);
	strcpy_s(temp, s.c_str());
	f.modify_line_data("goods.txt", n_line, temp);
	cout << "\n折扣价格应用成功!\n" << endl;
	
}