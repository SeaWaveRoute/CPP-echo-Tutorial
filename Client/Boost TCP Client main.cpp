#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main() {
	try {
		boost::asio::io_service io_service;
		//�⺻������ Boost Asio ���α׷��� �ϳ��� IO Service ��ü�� ����Ŵ.
		tcp::resolver resolver(io_service);
		//������ �̸��� TCP ���������� �ٲٱ����� Resolver�� ���.
		tcp::resolver::query query("localhost", "daytime");
		//�����δ� ���ü���, ���񽺴� Daytime ���������� �����ش�, token�� ����.
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		//DNS�� ���� IP �ּ� �� ��Ʈ��ȣ�� ��� �´�.
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		//���� ��ü�� �ʱ�ȭ�Ͽ� ������ �����Ѵ�.
		while (1) {
			boost::array<char, 128> buf;
			//�������� ��밡���ϸ� Ŭ������ ������ ��밡���� array
			boost::system::error_code error;
			//���� �� ���� ó�������� ����.
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			//���۸� �̿��Ͽ� �����κ��� �����͸� �޾ƿ�.
			if (error == boost::asio::error::eof)
				break
			else if (error)
				throw boost::system::system_error(error);
			cout.write(buf, data(), len);
			//���ۿ� ��� �����͸� ȭ�鿡 ����Ѵ�.
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}