#pragma once
#include "file.h"
class ServeGroup;
using Pclient = std::shared_ptr<ip::tcp::socket>;
class ClientGroup
{

public:
	string			m_name;		   //共享的根目录

	Pclient			_sock;
	file_packet_t	_pkt;				//要发送的包

	recv_pkt		_file_pkt;			//接收需要发送的目录

	ServeGroup      * m_serve;
	
	bool			_is_land;

	void  recv_head();
	void  recv_head_handle(const boost::system::error_code ec, size_t size);
	void  recv_date();
	void  recv_date_handle(const boost::system::error_code ec, size_t size);
	void  get_head();
	void  get_date();//初始化要发送的文件目录

	//int  handle_recv(const boost::system::error_code ec, size_t size);
	void type6();
	void type7();
	void type8();
	void type9();

	ClientGroup();
	~ClientGroup() = default;
private:

};
