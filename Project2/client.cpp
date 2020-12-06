#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")

int main(int argc, char* argv[])
{
	WORD sockVersion = MAKEWORD(2, 2);
	int SERVER_PORT = 6478;
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
	serAddr.sin_port = htons(SERVER_PORT);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(sclient, (sockaddr*)&serAddr, sizeof(serAddr)) ==SOCKET_ERROR)
	{
		printf("connect error !");
		closesocket(sclient);
		return 0;
	}
	char sentData[255],recData[255],sendata[255],recvData[255];
	while (1)
	{
		printf("传输明文:");
		gets_s(sentData);
		for (int i = 0; i<strlen(sentData); i++)
		sendata[i] = sentData[i] + 1;
		sendata[strlen(sentData)] = 0;
		send(sclient, sendata, strlen(sentData), 0);
		printf("加密后内容:%s\n",sendata);
		int ret = recv(sclient, recData, 255, 0);
		if (ret > 0)
		{
			recData[ret] = 0x00;
			printf("传回内容:%s\n",recData);
			for (int i = 0;i <= ret; i++)
			recData[i] = recData[i] - 1;
			recData[ret] = 0;
			printf("最终解密内容:");
			for (int i = 0; i <ret; i++)
			recvData[i] = recData[ret-1-i];
			recvData[ret] = 0;
			printf("%s\n\n",recvData);

		}
		if (strcmp(recData, "666")==0)
		{
			closesocket(sclient);
			WSACleanup();
			return 0;
		}
	}
}