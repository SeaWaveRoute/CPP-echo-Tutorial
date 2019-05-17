#include <iostream>
#include <string>
#include <winsock.h>
using namespace std;

void ShowErrorMessage(string message) {
	cout << "오류발생 : " << message << endl;
	system("pause");
	exit(1);
}

int main() {//Server main()함수
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddress, clientAddress;

	int serverPort = 9876;
	char received[256];
	int index = 1;//내가 while()문내 횟수확인위해 생성함

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("WSAStartup()");
	//Winsock을 초기화 (2, 2)는 winsock2.2버전을 의미.
	serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	//TCP 소켓을 생성
	if (serverSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");

	memset(&serverAddress, 0, sizeof(serverAddress));
	//serverAdress를 0으로 모두 초기화시켜주는 함수
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(serverPort);
	
	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("bind()");
	cout << "[현재상태] bind()" << endl;

	if (listen(serverSocket, 5) == SOCKET_ERROR)
		ShowErrorMessage("listen()");
	cout << "[현재상태] listen()" << endl;

	int sizeClientAddress = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &sizeClientAddress);
	cout << "[현재상태] accept()" << endl;

	if (clientSocket == INVALID_SOCKET)
		ShowErrorMessage("accept()");

	while (1) {//클라이언트의 메세지를 받아서 다시 전달.
		cout << " 몇번이 반복되었는가? " << index << endl;
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL;
		cout << "[클라이언트 메세지]: " << received << endl;
		cout << "[메세지 전송]: " << received << endl;
		if (strcmp(received, "[exit]") == 0) {
			send(clientSocket, received, sizeof(received) - 1, 0);
			cout << "[서버 main() 서버 종료]" << endl;
			break;
		}
		send(clientSocket, received, sizeof(received) - 1, 0);
		//sizeof() -1을 해주는 이유는 마지막\n문자를 없애주기위함.
		++index;
	}
	closesocket(clientSocket);
	closesocket(serverSocket);
	//Server에서 server와 clientSocket을 닫아야한다.
	WSACleanup();
	system("pause");
	return 0;
}