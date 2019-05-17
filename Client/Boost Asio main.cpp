#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

int main() {
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	//deadline_timer�� �����Ͽ� 5�ʰ��� �ð��� �Է�.
	t.wait();
	//wait()�Լ��� �̿��Ͽ� �Էµ� 5�ʸ�ŭ wait�ϰ���.
	cout << "Hello World" << endl;

	system("pause");
	return 0;
}