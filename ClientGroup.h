#pragma once
#include "file.h"
class ServeGroup;
using Pclient = std::shared_ptr<ip::tcp::socket>;
class ClientGroup
{

public:
	string			m_name;		   //����ĸ�Ŀ¼

	Pclient			_sock;
	file_packet_t	_pkt;				//Ҫ���͵İ�

	recv_pkt		_file_pkt;			//������Ҫ���͵�Ŀ¼

	ServeGroup      * m_serve;
	
	bool			_is_land;

	void  recv_head();
	void  recv_head_handle(const boost::system::error_code ec, size_t size);
	void  recv_date();
	void  recv_date_handle(const boost::system::error_code ec, size_t size);
	void  get_head();
	void  get_date();//��ʼ��Ҫ���͵��ļ�Ŀ¼

	//int  handle_recv(const boost::system::error_code ec, size_t size);
	void type6();
	void type7();
	void type8();
	void type9();

	ClientGroup();
	~ClientGroup() = default;
private:

};
