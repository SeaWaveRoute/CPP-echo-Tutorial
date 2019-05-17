#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

int main() {
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	//deadline_timer를 생성하여 5초간의 시간을 입력.
	t.wait();
	//wait()함수를 이용하여 입력된 5초만큼 wait하게함.
	cout << "Hello World" << endl;

	system("pause");
	return 0;
}