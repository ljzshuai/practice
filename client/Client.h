#include "file.h"
#include "boost\asio.hpp"
using namespace boost::asio;
class Client
{
public:

	Client(io_service &ios,const string & path_save);
	void  connect_m(ip::tcp::endpoint& ep,string path_down);

	void recv_head();
	void recv_date();
	void get_head();
	void get_date();

	void type0();
	void type1();
	void type2();
	void type3();
private:

	recv_pkt         _file_pkt;
	ip::tcp::socket  _sock;
	file_packet_t *  _pkt;
	FILE *			 _file;
	string           _path_save;

};
