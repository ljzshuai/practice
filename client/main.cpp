//#include <iostream>
//#include <string>
//#include <boost/asio.hpp>
//#include <boost/bind.hpp>
//#include <boost/smart_ptr.hpp>
//using namespace boost::asio;
//using boost::system::error_code;
//using ip::tcp;
//struct CHelloWorld_Service{
//	CHelloWorld_Service(io_service &iosev)
//	:m_iosev(iosev), m_acceptor(iosev, tcp::endpoint(tcp::v4(), 1000))
//	{
//	}
//	void start()
//	{
//		boost::shared_ptr<tcp::socket> psocket(new tcp::socket(m_iosev));
//		m_acceptor.async_accept(*psocket,
//			boost::bind(&CHelloWorld_Service::accept_handler, this, psocket, _1)
//			);
//	}
//
//	void accept_handler(boost::shared_ptr<tcp::socket> psocket, error_code ec)
//	{
//		if (ec) return;
//		start();
//		std::cout << psocket->remote_endpoint().address() << std::endl;
//
//		boost::shared_ptr<std::string> pstr(new std::string("hello async world!"));
//		psocket->async_write_some(buffer(*pstr),
//			boost::bind(&CHelloWorld_Service::write_handler, this, pstr, _1, _2)
//			);
//	}
//	void write_handler(boost::shared_ptr<std::string> pstr,
//		error_code ec, size_t bytes_transferred)
//	{
//		if (ec)
//			std::cout << "·¢ËÍÊ§°Ü!" << std::endl;
//		else
//			std::cout << *pstr << " ÒÑ·¢ËÍ" << std::endl;
//	}
//private:
//	io_service &m_iosev;
//	ip::tcp::acceptor m_acceptor;
//};
#include<iostream>
#include<memory>
#include<boost\asio.hpp>
#include"Client.h"

int main(int argc, char* argv[])
{
	boost::asio::io_service ios;
	boost::asio::ip::address addr;
	addr = addr.from_string("127.0.0.1");
	boost::asio::ip::tcp::endpoint ep(addr, 8001);

	std::shared_ptr<Client> client = make_shared<Client>(ios,"E:\\WorkSpace");
	client->connect_m(ep,"c_test");



	ios.run();
	return 0;
}