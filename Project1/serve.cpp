#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")
int main(int argc, char* argv[])
{
	//��ʼ��WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	//�����׽���
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}
	//��IP�Ͷ˿�
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(5264);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}
	//��ʼ����
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}
	SOCKET sClient;
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[255];
	char sendData[255];
	printf("�ȴ�����...\n");
	sClient = accept(slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
	if (sClient == INVALID_SOCKET)
	{
		printf("accept error !");
		closesocket(sClient);
		closesocket(slisten);
		WSACleanup();
		return 0;
	}
	printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));
	//��������
	while (1)
	{

		int ret = recv(sClient, revData, 255, 0);
		if (ret > 0)
		{
			revData[ret] = 0x00;
			printf("����������:%s\n", revData);
		}
		for (int i = 0; i <ret; i++)
		sendData[i] = revData[i] - 1;
		sendData[ret] = 0x00;
		printf("�ѽ�������:%s\n", sendData);
		send(sClient, sendData, strlen(sendData), 0);
		if(strcmp(sendData, "666")==0)
		{
			closesocket(sClient);
			closesocket(slisten);
			WSACleanup();
			return 0;
		}
	}
}