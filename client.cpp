#define PORT 2021
#define BUFFER_LEN 1024
#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)//��strcpy_s�Ĵ�����ʾ����
using namespace std;

int main()
{
	//���峤�ȱ���
	int send_len = 0;
	int recv_len = 0;
	int len = 0;
	//���巢�ͻ������ͽ��ܻ�����
	char send_buf[BUFFER_LEN] = { '\0' };
	char recv_buf[BUFFER_LEN] = { '\0' };
	//���������׽��֣����������׽���
	SOCKET s_server;
	SOCKET s_accept;
	//����˵�ַ�ͻ��˵�ַ
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	//��ʼ���׽��ֿ�
	WORD w_req = MAKEWORD(2, 2);//�汾��
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
	else cout << "��ʼ���׽��ֿ�ɹ���" << endl;

	//���汾��
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
	{
		cout << "�׽��ֿ�汾�Ų�����" << endl;
		WSACleanup();
	}
	else cout << "�׽��ֿ�汾��ȷ��" << endl;

	//������˵�ַ��Ϣ

	//���������Ϣ
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);
	//�����׽���
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "�׽��ְ�ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else cout << "�׽��ְ󶨳ɹ���" << endl;

	//�����׽���Ϊ����״̬
	if (listen(s_server, SOMAXCONN) < 0)
	{
		cout << "���ü���״̬ʧ�ܣ�" << endl;
		WSACleanup();
	}
	else cout << "���ü���״̬�ɹ���" << endl;
	cout << "�ͻ������ڼ������ӣ����Ժ�...." << endl;
	//������������
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR)
	{
		cout << "����ʧ�ܣ�" << endl;
		WSACleanup();
		return 0;
	}
	cout << "���ӽ�����׼����������" << endl;
	//��������
	while (TRUE)
	{
		char input[10];
		memset(recv_buf, 0, sizeof(recv_buf));
		recv_len = recv(s_accept, recv_buf, BUFFER_LEN, 0);
		if (recv_len < 0)
		{
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
		else cout << recv_buf << endl;
		if (recv_buf[1] == '$'||recv_buf[0]=='$')
		{
			
			memset(send_buf, 0, sizeof(send_buf));
			cin >> input;
			strcpy_s(send_buf, input);
			send_len = send(s_accept, send_buf, sizeof(send_buf), 0);
			if (send_len < 0) { cout << "����ʧ��\n"; break; }
		}
		if (recv_buf[0] == '@') break;


	}
	//�ر��׽���
	closesocket(s_server);
	closesocket(s_accept);
	//�ͷ�DLL��Դ
	WSACleanup();
	return 0;
}
