#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <winsock.h>
using namespace std;

void ShowErrorMessage(string message) {
	cout << "오류발생 : " << message << endl;
	system("pause");
	exit(1);
}

int main() {//Client main함수
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress;
	//Server main함수에서는 server, client를 다만들었지만
	//Client main함수에서는 clientSocket과 serverAddress를 생성
	int serverPort = 9876;//Server와 Client Port값은 같아야함.
	char received[256];
	string sent;//Server로 보내는 내용을 저장하기위해 생성한다.

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("WSAStartup()");
	//winsock을 초기화하기위해 wsaData을 생성해주는것!!!
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	//TCP 소케슬 생성하기위해 clientSocket을 생성해주는것!!!

	if (clientSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");
	//TCP 소켓이 유효하지않을경우 Error표시해주기위함.

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	//문자열 IP를 네트워크 바이트형식으로 표현
	serverAddress.sin_port = htons(serverPort);
	//2바이트 정수 네트워크 바이트 형식으로 표현

	if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("connect()");
	cout << "[현재상태] connect()" << endl;

	while(1) {//반복적으로 서버로 메세지를 전송하고 에코메세지를 받음
		cout << "[메세지를 전송]: ";
		getline(cin, sent);
		//cin을 통해 버퍼 입력을 하고 sent에 저장한다.
		if (sent == "") continue;
		//sent에 공백이 들어갈때 그대로 사용하기위해 작성함.
		send(clientSocket, sent.c_str(), sent.length(), 0);
		//Client에서 Server로 메세지를 전송해줌.
		//입력받은 string타입을 c_str, c언어 str타입으로 변경해주고
		//sent.length()문자열의 길이를 같이 보내줌.
		int length = recv(clientSocket, received, sizeof(received), 0);
		//Server로부터 received로 받아 주는 함수?
		received[length] = '\0';
		if (strcmp(received, "[exit]") == 0) {
			//Server로부터 받은 echo메세지가 [exit]일경우
			//서버를 종료하는 구문.
			cout << "[클라이언트 main() 서버 종료]" << endl;
			break;
		}
		cout << "[서버 메세지] : " << received << endl;
		//[exit]이 아닐경우 echo메세지를 띄어주는 부분
	}
	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
}