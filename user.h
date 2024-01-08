#pragma once
#define BUYER 0
#define SELLER 1
#define ACCOUT_LEN 10
#define PASSWORD_LEN 10

#include<cstdio>
#include<iostream>
#include<cstring>
#include<fstream>
#include<string>
#include"file.h"

using namespace std;

class user 
{
	int type=0;//0�������ߣ�1���̼�
	string accout;
	string password;
public:
	virtual int get_user_type()=0;
	void enroll();// ע��
	string login() const; // ��¼
	void change_password();// �޸�����
	
};


class buyer : public user//�̳��ࣺ������
{    
	unsigned int remain=0;
public:
	int get_user_type() { return BUYER; };
	unsigned int ask_money(string accout)const;// �˺������Ĳ�ѯ
	void recharge(int money,string accout);// ��ֵ
	void consume(int money, string accout);// ����
};


class  seller : public user {   //�̳��ࣺ����
public:
	int get_user_type() { return SELLER; };
};


 void user:: enroll()//ע��
{
	 file f;
	 string temp;
	 fstream file("user.txt", ios::app);
	 if (!file)
	 {
		 cout << "�ļ���ʧ�ܣ�" << endl;
		 return;
	 }

	 cout << "������Ҫע����˻�������" <<ACCOUT_LEN<<"���ַ�����)"<< endl;
	 cin >> temp;	
	 while (temp.size() >= ACCOUT_LEN)//�жϳ���
	 {
		 cout << "��������˻������������������룺" << endl;
		 cin >> temp;
	 }
	 while (f.find_in_file("user.txt",temp))//�ж��Ƿ��ظ�
	 {
		 cout << "���û����ѱ�ע�ᣬ���������룺" << endl;
		 cin >> temp;
	 }
	 file << temp << endl;//ÿ�д�һ���˻�
	 
	 cout << "�������������룺" << endl;
	 cin >> temp;
	 file << temp << endl;//�˻�����һ�д�����

	 file << "0" << endl;//��ʼ���Ĭ��Ϊ0

	 cout << "ע��ɹ���" << endl;
	 file.close();
}






 string user::login() const
 {
	 string accout_in;
	 string password_in,password_file;
	 int n_line;
	 file f;
	 char data[10] = {0};
	 cout << "�����������û�����";
	 cin >> accout_in;
	 n_line = f.find_in_file("user.txt",accout_in);//�õ����˻����ڵ�����
	 while (n_line==0)
	 {
		 cout << "��������û���δע�ᣬ���������룺" << endl;
		 cin >> accout_in;
		 n_line = f.find_in_file("user.txt",accout_in);
	 }
	 n_line++;//������������
	 cout << "�������������룺" << endl;
	 cin >> password_in;
	 strcpy_s(data,f.read_line_data("user.txt", n_line));
	 password_file = f.char_to_str(data);
	 while (password_in!=password_file)
	 {
		 cout << "����������������룺" << endl;
		 cin >> password_in;
	 }
	 cout << "��¼�ɹ���" << endl;
	 return accout_in;
 }


 void user::change_password()
 {
	 string accout_in;
	 char password_new[10];
	 int n_line=0;
	 file f;
	 cout << "�������˻�����" << endl;
	 cin >> accout_in;
	 cout << "�������µ����룺" << endl;
	 cin >> password_new;
	 n_line = f.find_in_file("user.txt", accout_in);
	 n_line++;//ָ��������
	 f.modify_line_data("user.txt", n_line, password_new);
 }
 
 unsigned int buyer::ask_money(string accout) const// �˺������Ĳ�ѯ
 {
	 file f;
	 string temp;
	 int n_remain;
	 int n_line = 0;
	 char remain[10] = { 0 };
	
	 n_line = f.find_in_file("user.txt", accout);
	 n_line+=2;//ָ�������
	 strcpy_s(remain, f.read_line_data("user.txt", n_line));
	 temp = remain;//Ϊ��ת��Ϊint����ת��Ϊstring
	 n_remain = stoi(temp);
	 return n_remain;
 }

 void buyer:: recharge(int money,string accout) 
 {
	 string accout_in;
	 string temp;
	 file f;
	 int n_line = 0;
	 int remain = 0;
	 
	 char remain_new[10] = { 0 };
	

	 n_line = f.find_in_file("user.txt", accout);
	 n_line += 2;//ָ������У�
	 remain = ask_money(accout);
	 remain += money;
	 temp = to_string(remain);
	 strcpy_s(remain_new,temp.data());
	 f.modify_line_data("user.txt", n_line, remain_new);
	 cout << "��ֵ�ɹ���" << endl;
 }

 void buyer::consume(int money, string accout)
 {
	 string accout_in;
	 string temp;
	 file f;
	 int n_line = 0;
	 int remain = 0;
	 char remain_new[10] = { 0 };
	
	 n_line = f.find_in_file("user.txt", accout);
	 n_line += 2;//ָ������У�
	 remain = ask_money(accout);
	 remain -= money;
	 temp = to_string(remain);
	 strcpy_s(remain_new, temp.data());
	 f.modify_line_data("user.txt", n_line, remain_new);
	 cout << "���ѳɹ���" << endl;

 }