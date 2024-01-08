
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
	string seller;//����Ʒ�����̼�
	float price;
	int type;
	int left;
	

	virtual float get_price() = 0;
	virtual int get_type() = 0;
	void add(string belong);//�����Ʒ
	void show() const;//չʾ��Ʒ
	void search() const ;//Ѱ����Ʒ
	void discount(float n,int type);//���ۻ
	void change_left();//����ʣ����
	void change_price();//���ļ۸�


};

class food :public goods {
	
public:
	float get_price() { return price; };//�õ��۸�
	int get_type() { return FOOD; };//�õ�����
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
	cout << "�������������Ʒ���ƣ�" << endl;
	cin >> name_in;
	iofile << name_in << endl;

	iofile << belong << endl;//д�������̼��˺�

	cout << "�������������Ʒ�۸�" << endl;
	cin >> price_in;
	iofile << price_in << endl;

	iofile << get_type() << endl;//д������

	cout << "�������������Ʒʣ����������������" << endl;
	cin >> left_in;
	iofile << left_in << endl;
	cout << "����Ʒ�ѳɹ���ӣ�" << endl;
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
		cout << "��Ʒ" << n << endl;//���

		cout << "���ƣ�" << s << endl;
		getline(iofile, s);
		cout << "�����̼ң�" << s << endl;
		getline(iofile, s);
		cout << "�۸�" << s << "Ԫ"<<endl;
		getline(iofile, s);
		type = stoi(s);
		switch (type)
		{
			case FOOD: cout << "���ͣ�ʳ��" << endl; break;
			case CLOTHES: cout << "���ͣ�����" << endl; break;
			case BOOK:cout << "���ͣ��鼮" << endl;
		}
		getline(iofile, s);
		left = stoi(s);
		cout << "ʣ������" << left << endl;
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
	cout << "������Ҫ���ĵ���Ʒ����" << endl;
	cin >> name_in;
	cout << "��������ĺ��ʣ������" << endl;
	cin >> left_in;
	line_n=f.find_in_file("goods.txt", name_in);//������Ʒ�����ҵ� ���ڵ�����
	line_n += 4;//ʣ����������
	f.modify_line_data("goods.txt", line_n, left_in);//����left
}

void goods:: change_price()
{
	string name_in;
	char price_in[10] = {10};
	int line_n;
	file f;
	fstream iofile("goods.txt", ios::in | ios::app);
	cout << "������Ҫ���ĵ���Ʒ����" << endl;
	cin >> name_in;
	cout << "��������ĺ�ļ۸�" << endl;
	cin >> price_in;
	
	line_n = f.find_in_file("goods.txt", name_in);//������Ʒ�����ҵ� ���ڵ�����
	line_n += 2;//ʣ����������
	f.modify_line_data("goods.txt", line_n, price_in);//����left
}


void goods::search() const
{
	//�������ƶ���Ʒ��������
	string name_in;
	file f;
	int line_n;
	fstream iofile("goods.txt", ios::in | ios::out);
	char belong_file[10] = { 0 };
	char price_file[10] = { 0 };
	char type_file[10] = { 0 };
	char left_file[10] = { 0 };
	char temp[10] = { 0 };
	cout << "������Ҫ��������Ʒ���ƣ�" << endl;
	cin >> name_in;
	line_n=f.find_in_file("goods.txt", name_in);
	while (line_n == 0)
	{
		cout << "δ�ҵ�����Ʒ���������������ƣ�" << endl;
		cin >> name_in;
		line_n = f.find_in_file("goods.txt", name_in);
	}
	strcpy_s(belong_file, f.read_line_data("goods.txt", line_n + 1));
	strcpy_s(price_file,f.read_line_data("goods.txt",line_n + 2));
	strcpy_s(type_file, f.read_line_data("goods.txt", line_n + 3));
	strcpy_s(left_file, f.read_line_data("goods.txt", line_n + 4));
	
	cout << "���ƣ�" << name_in << endl;
	cout << "�����̼ң�" << belong_file << endl;
	cout << "�۸�" << price_file << endl;
	if(!strcmp(type_file,"1")) cout<<"���ͣ�ʳƷ"<<endl;
	if(!strcmp(type_file, "2")) cout << "���ͣ�����" << endl;
	if(!strcmp(type_file, "2")) cout << "���ͣ��鼮" << endl;
	cout << "ʣ������" << left_file << endl;
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
	
	while (type !=FOOD && type != CLOTHES && type != BOOK) { cout << "����Ƿ������������룺" << endl; cin >> type;}
	s = to_string(type);
	n_line = f.find_in_file("goods.txt", s);
	n_line--;//ָ��۸���
	strcpy_s(temp, f.read_line_data("goods.txt", n_line));
	s = f.char_to_str(temp);
	money = stof(s);
	money = money * n;//����
	s = to_string(money);
	strcpy_s(temp, s.c_str());
	f.modify_line_data("goods.txt", n_line, temp);
	cout << "\n�ۿۼ۸�Ӧ�óɹ�!\n" << endl;
	
}