#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"WS2_32")
int main()
{
	WSADATA swadata;
	WORD sockVersion=MAKEWORD(2,0);//winsock�İ汾2.0
	WSAStartup(sockVersion,&swadata);//����WInsock�⣬swadata���ؿ����Ϣ

   //�����׽���
	SOCKET s=::socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("Creat scoket is failed!\n");
		::WSACleanup();
		system("pause");
		return 0;
	}
	//���socaddr_in�ṹ
	sockaddr_in sin;
	sin.sin_family=AF_INET;
	sin.sin_port=htons(8866);//1024--65535�Ķ˿ں�
	sin.sin_addr.S_un.S_addr=INADDR_ANY;
	//������׽��ֵ����ص�ַ
	if(::bind(s,(SOCKADDR*)&sin,sizeof(sin))==SOCKET_ERROR)
	{
		printf("bind is failed!\n");
		::WSACleanup();
		system("pause");
		return 0;
	}
	//����ģʽ
	if(::listen(s,2)==SOCKET_ERROR)
	{
		printf("listen is failed!\n");
		::WSACleanup();
		system("pause");
		return 0;
	}
	printf("���ڼ���....\n");

	//ѭ��������������
	sockaddr_in addrlink;
	int Len=sizeof(addrlink);
	char anser[]="HTTP/1.1 200 OK\r\n\r\n<html><head><title></title></head><body>yours</body></html>\r\n";
	char buf[1024];
	SOCKET client;
	while(1)
	{
		client=::accept(s,(SOCKADDR*)&addrlink,&Len);
		if(client==INVALID_SOCKET)
		{
			printf("accept is failed!");
			continue;
		}
		int n;
		while((n=::recv(client,buf,1024,0))==0);
		buf[n]='\0';
		printf("�ͻ�:(%s)",inet_ntoa(addrlink.sin_addr));
		printf("\n%s\n",buf);
		::send(client,anser,strlen(anser),0);	
	}
   	::closesocket(client);
	::closesocket(s);
	::WSACleanup();
	return 0;

}