#define PORT 2021
#define BUFFER_LEN 1024
#include<iostream>
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)//把strcpy_s的错误提示消除
using namespace std;

int main()
{
	//定义长度变量
	int send_len = 0;
	int recv_len = 0;
	int len = 0;
	//定义发送缓冲区和接受缓冲区
	char send_buf[BUFFER_LEN] = { '\0' };
	char recv_buf[BUFFER_LEN] = { '\0' };
	//定义服务端套接字，接受请求套接字
	SOCKET s_server;
	SOCKET s_accept;
	//服务端地址客户端地址
	SOCKADDR_IN server_addr;
	SOCKADDR_IN accept_addr;
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) cout << "初始化套接字库失败！" << endl;
	else cout << "初始化套接字库成功！" << endl;

	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
	{
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else cout << "套接字库版本正确！" << endl;

	//填充服务端地址信息

	//填充服务端信息
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);
	//创建套接字
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "套接字绑定失败！" << endl;
		WSACleanup();
	}
	else cout << "套接字绑定成功！" << endl;

	//设置套接字为监听状态
	if (listen(s_server, SOMAXCONN) < 0)
	{
		cout << "设置监听状态失败！" << endl;
		WSACleanup();
	}
	else cout << "设置监听状态成功！" << endl;
	cout << "客户端正在监听连接，请稍候...." << endl;
	//接受连接请求
	len = sizeof(SOCKADDR);
	s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
	if (s_accept == SOCKET_ERROR)
	{
		cout << "连接失败！" << endl;
		WSACleanup();
		return 0;
	}
	cout << "连接建立，准备接受数据" << endl;
	//接收数据
	while (TRUE)
	{
		char input[10];
		memset(recv_buf, 0, sizeof(recv_buf));
		recv_len = recv(s_accept, recv_buf, BUFFER_LEN, 0);
		if (recv_len < 0)
		{
			cout << "接受失败！" << endl;
			break;
		}
		else cout << recv_buf << endl;
		if (recv_buf[1] == '$'||recv_buf[0]=='$')
		{
			
			memset(send_buf, 0, sizeof(send_buf));
			cin >> input;
			strcpy_s(send_buf, input);
			send_len = send(s_accept, send_buf, sizeof(send_buf), 0);
			if (send_len < 0) { cout << "发送失败\n"; break; }
		}
		if (recv_buf[0] == '@') break;


	}
	//关闭套接字
	closesocket(s_server);
	closesocket(s_accept);
	//释放DLL资源
	WSACleanup();
	return 0;
}
