#define _CRT_SECURE_NP_WARNINGS
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;
//�ش�tcp namespace�� �������� �Ǿ��ִ��� Ȯ���ʿ�.

string make_daytime_string() {
	time_t now = time(0);
	return ctime(&now);
	//�ð������� �����Ͽ� ���� ��ǻ���� ���� ��¥ �� �ð��� ����.
	//�ش� �ڵ�� �ʿ��Ҷ����� ã�ƺ��°� �ո���.
}
int main() {
	try {
		boost::asio::io_service io_service;
		//�⺻������ Boost Asio ���α׷��� �ϳ��� IO Service ��ü�� ����.
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13)));
		//TCP ���������� 13�� ��Ʈ�� ������ �޴� ���� ������ ����.
		while (1) {// ��� Ŭ���̾�Ʈ�� ���� ���ѷ���
			tcp::socket socket(io_service);
			//���� ��ü�� �����Ͽ� ���.
			acceptor.accept(socket);
			string message = make_daytime_string();
			//Ŭ���̾�Ʈ�� ������ �Ϸ�Ǹ� ���� �޼����� ����.
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(messate), ignored_error);
			//�ش� Ŭ���̾�Ʈ���� �޼����� ��� ����.
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;


	}
	return 0;
}