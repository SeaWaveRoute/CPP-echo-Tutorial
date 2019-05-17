#define _CRT_SECURE_NP_WARNINGS
#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;
//해당tcp namespace는 무엇으로 되어있는지 확인필요.

string make_daytime_string() {
	time_t now = time(0);
	return ctime(&now);
	//시간변수를 생성하여 서버 컴퓨터의 현재 날짜 및 시간을 리턴.
	//해당 코드는 필요할때마다 찾아보는게 합리적.
}
int main() {
	try {
		boost::asio::io_service io_service;
		//기본적으로 Boost Asio 프로그램은 하나의 IO Service 객체를 가짐.
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13)));
		//TCP 프로토콜의 13번 포트로 연결을 받는 수동 소켓을 생성.
		while (1) {// 모든 클라이언트에 대해 무한루프
			tcp::socket socket(io_service);
			//소켓 객체를 생성하여 대기.
			acceptor.accept(socket);
			string message = make_daytime_string();
			//클라이언트와 연결이 완료되면 보낼 메세지를 생성.
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(messate), ignored_error);
			//해당 클라이언트에게 메세지를 담아 전송.
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;


	}
	return 0;
}