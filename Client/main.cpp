#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <winsock.h>
using namespace std;

void ShowErrorMessage(string message) {
	cout << "�����߻� : " << message << endl;
	system("pause");
	exit(1);
}

int main() {//Client main�Լ�
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress;
	//Server main�Լ������� server, client�� �ٸ��������
	//Client main�Լ������� clientSocket�� serverAddress�� ����
	int serverPort = 9876;//Server�� Client Port���� ���ƾ���.
	char received[256];
	string sent;//Server�� ������ ������ �����ϱ����� �����Ѵ�.

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("WSAStartup()");
	//winsock�� �ʱ�ȭ�ϱ����� wsaData�� �������ִ°�!!!
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	//TCP ���ɽ� �����ϱ����� clientSocket�� �������ִ°�!!!

	if (clientSocket == INVALID_SOCKET)
		ShowErrorMessage("socket()");
	//TCP ������ ��ȿ����������� Errorǥ�����ֱ�����.

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	//���ڿ� IP�� ��Ʈ��ũ ����Ʈ�������� ǥ��
	serverAddress.sin_port = htons(serverPort);
	//2����Ʈ ���� ��Ʈ��ũ ����Ʈ �������� ǥ��

	if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("connect()");
	cout << "[�������] connect()" << endl;

	while(1) {//�ݺ������� ������ �޼����� �����ϰ� ���ڸ޼����� ����
		cout << "[�޼����� ����]: ";
		getline(cin, sent);
		//cin�� ���� ���� �Է��� �ϰ� sent�� �����Ѵ�.
		if (sent == "") continue;
		//sent�� ������ ���� �״�� ����ϱ����� �ۼ���.
		send(clientSocket, sent.c_str(), sent.length(), 0);
		//Client���� Server�� �޼����� ��������.
		//�Է¹��� stringŸ���� c_str, c��� strŸ������ �������ְ�
		//sent.length()���ڿ��� ���̸� ���� ������.
		int length = recv(clientSocket, received, sizeof(received), 0);
		//Server�κ��� received�� �޾� �ִ� �Լ�?
		received[length] = '\0';
		if (strcmp(received, "[exit]") == 0) {
			//Server�κ��� ���� echo�޼����� [exit]�ϰ��
			//������ �����ϴ� ����.
			cout << "[Ŭ���̾�Ʈ main() ���� ����]" << endl;
			break;
		}
		cout << "[���� �޼���] : " << received << endl;
		//[exit]�� �ƴҰ�� echo�޼����� ����ִ� �κ�
	}
	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
}