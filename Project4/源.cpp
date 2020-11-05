#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")

int main(int argc, char* argv[])
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket !");
		return 0;
	}
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(5264);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) ==
		SOCKET_ERROR)
	{
		printf("connect error !");
		closesocket(sclient);
		return 0;
	}
	char sentData[255], recData[255];
	while (1)
	{
		printf("对象B:");
		gets_s(sentData);
		send(sclient, sentData, strlen(sentData), 0);
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0)
		{
			recData[ret] = 0x00;
			printf("对象A:%s\n", recData);
		}
		if (strcmp(sentData,"ByeBye")==0||strcmp(recData, "ByeBye")==0)
		{
			closesocket(sclient);
			WSACleanup();
			return 0;
		}
	}
}