#include "RecvSocket.h"
#include <boost\asio.hpp>
using namespace boost::asio;
int main()
{
	io_service ios;
	ip::address addr;
	addr = addr.from_string("127.0.0.1");
	ip::tcp::endpoint ep(addr, 8001);

	std::shared_ptr<RecvSocket> Pserve = std::make_shared<RecvSocket>(ep, ios);

	Pserve->accept_start("E:\\vc13\\c_test");

	ios.run();

}
