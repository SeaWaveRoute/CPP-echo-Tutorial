#include <iostream>
#include <string>
#include <winsock.h>
using namespace std;

void ShowErrorMessage(string message) {
	cout << "�����߻� : " << message << endl;
	system("pause");
	exit(1);
}

int main() {//Server main()�Լ�
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddress, clientAddress;

	int serverPort = 9876;
	char received[256];
	int index = 1;//���� while()���� Ƚ��Ȯ������ ������

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("WSAStartup()");
	//Winsock�� �ʱ�ȭ (2, 2)�� winsock2.2������ �ǹ�.
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	//TCP ������ ����
	if (serverSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");

	memset(&serverAddress, 0, sizeof(serverAddress));
	//serverAdress�� 0���� ��� �ʱ�ȭ�����ִ� �Լ�
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(serverPort);
	
	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("bind()");
	cout << "[�������] bind()" << endl;

	if (listen(serverSocket, 5) == SOCKET_ERROR)
		ShowErrorMessage("listen()");
	cout << "[�������] listen()" << endl;

	int sizeClientAddress = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &sizeClientAddress);
	cout << "[�������] accept()" << endl;

	if (clientSocket == INVALID_SOCKET)
		ShowErrorMessage("accept()");

	while (1) {//Ŭ���̾�Ʈ�� �޼����� �޾Ƽ� �ٽ� ����.
		cout << " ����� �ݺ��Ǿ��°�? " << index << endl;
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL;
		cout << "[Ŭ���̾�Ʈ �޼���]: " << received << endl;
		cout << "[�޼��� ����]: " << received << endl;
		if (strcmp(received, "[exit]") == 0) {
			send(clientSocket, received, sizeof(received) - 1, 0);
			cout << "[���� main() ���� ����]" << endl;
			break;
		}
		send(clientSocket, received, sizeof(received) - 1, 0);
		//sizeof() -1�� ���ִ� ������ ������\n���ڸ� �����ֱ�����.
		++index;
	}
	closesocket(clientSocket);
	closesocket(serverSocket);
	//Server���� server�� clientSocket�� �ݾƾ��Ѵ�.
	WSACleanup();
	system("pause");
	return 0;
}