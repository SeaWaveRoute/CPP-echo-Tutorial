#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main() {
	try {
		boost::asio::io_service io_service;
		//기본적으로 Boost Asio 프로그램은 하나의 IO Service 객체를 가리킴.
		tcp::resolver resolver(io_service);
		//도메인 이름을 TCP 종단점으로 바꾸기위해 Resolver를 사용.
		tcp::resolver::query query("localhost", "daytime");
		//서버로는 로컬서버, 서비스는 Daytime 프로토콜을 적어준다, token과 같음.
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		//DNS를 거쳐 IP 주소 및 포트번호를 얻어 온다.
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		//소켓 객체를 초기화하여 서버에 연결한다.
		while (1) {
			boost::array<char, 128> buf;
			//정적으로 사용가능하며 클래스를 변수로 사용가능한 array
			boost::system::error_code error;
			//버퍼 및 오류 처리벼수를 선언.
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			//버퍼를 이용하여 서버로부터 데이터를 받아옴.
			if (error == boost::asio::error::eof)
				break
			else if (error)
				throw boost::system::system_error(error);
			cout.write(buf, data(), len);
			//버퍼에 담긴 데이터를 화면에 출력한다.
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}