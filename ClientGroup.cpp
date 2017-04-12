#include "ClientGroup.h"
#include "ServeGroup.h"


ClientGroup::ClientGroup()
	:_is_land(0)
{
	
}

void ClientGroup::get_head()
{
	std::cout << "get_head" << std::endl;
	int time = _file_pkt._buf_used - _file_pkt._head_sz;
	for (int i = 0; i != time; ++i)
	{
		if (strncmp(_file_pkt._buf + i, (char *)&_file_pkt._head_id, sizeof(_file_pkt._head_id)) == 0){
			memmove(_file_pkt._buf, _file_pkt._buf + i, sizeof(file_packet_t)-i);
			_file_pkt._buf_used -= i;
			file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;
			if (_file_pkt._buf_used >= tmp->_header._mlen){
				get_date();
				return;
			}
			recv_date();
			return;
		}
	}
	memmove(_file_pkt._buf, _file_pkt._buf + time, sizeof(file_packet_t)-time);
	_file_pkt._buf_used -= time;
	recv_head();
}

void ClientGroup::recv_head_handle(const boost::system::error_code ec, size_t size)
{

	std::cout << "头的大小  " << size << std::endl;
	if (!size)
	{
		m_serve->erase_client(this);
		return;
	}
	_file_pkt._buf_used += size;
	if (_file_pkt._buf_used >= _file_pkt._head_sz){
		get_head();
		return;
	}
	recv_head();
}
void ClientGroup::recv_date_handle(const boost::system::error_code ec, size_t size)
{
	std::cout << "路径的大小  " << size << std::endl;
	if (!size)
	{
		m_serve->erase_client(this);
		return;///////////////////////
	}
	_file_pkt._buf_used += size;
	file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;

	if (_file_pkt._buf_used >= tmp->_header._mlen){
		get_date();
		return;
	}
	recv_date();
}
void ClientGroup::recv_head()
{
	if (_file_pkt._buf_used >= _file_pkt._head_sz){
		get_head();
		return;
	}
	std::cout << "等待接收头" << std::endl;
	this->_sock->async_read_some(buffer((void*)(_file_pkt._buf + _file_pkt._buf_used), sizeof(file_packet_t)),
		std::bind(&ClientGroup::recv_head_handle, this, std::placeholders::_1, std::placeholders::_2)
		);
}
void ClientGroup::recv_date()
{

	std::cout << "等待接收path" << std::endl;
	this->_sock->async_read_some(buffer((void*)(_file_pkt._buf + _file_pkt._buf_used)
		,sizeof(file_packet_t))
		,std::bind(&ClientGroup::recv_date_handle, this, std::placeholders::_1, std::placeholders::_2)
		);

}

void ClientGroup::get_date()
{
	std::cout << "get_date" << std::endl;
	file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;

	if (tmp->_header._type == 9)
	{
		int a;
	}

	switch (tmp->_header._type)
	{
	case 6:
		type6(); return;
	case 7:
		type7(); return;
	case 8:
		type8(); return;
	case 9:
		type9(); return;
	default:
		return;
	}

}

void ClientGroup::type6() //发送到group的信息
{
	std::cout << "6" << std::endl;
	file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;





	_file_pkt._buf_used -= tmp->_header._mlen;
	memmove(_file_pkt._buf, _file_pkt._buf + tmp->_header._mlen, sizeof(file_packet_t)-tmp->_header._mlen);
	recv_head();
}
void ClientGroup::type7() //private 私聊的信息
{
	std::cout << "7" << std::endl;
	file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;





	_file_pkt._buf_used -= tmp->_header._mlen;
	memmove(_file_pkt._buf, _file_pkt._buf + tmp->_header._mlen, sizeof(file_packet_t)-tmp->_header._mlen);
	recv_head();
}
void ClientGroup::type8() //需要第一次获取文件列表
{
	std::cout << "8" << std::endl;
	file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;





	_file_pkt._buf_used -= tmp->_header._mlen;
	memmove(_file_pkt._buf, _file_pkt._buf + tmp->_header._mlen, sizeof(file_packet_t)-tmp->_header._mlen);
	recv_head();
}
void ClientGroup::type9() //登陆用户名
{
	std::cout << "9" << std::endl;
	file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;
	m_name = tmp->_mdata;
	m_serve->add_client(this, m_name);
	
	m_serve->erase_alive(this);

	_file_pkt._buf_used -= tmp->_header._mlen;
	memmove(_file_pkt._buf, _file_pkt._buf + tmp->_header._mlen, sizeof(file_packet_t)-tmp->_header._mlen);
	recv_head();
}

/*
std::cout << "8" << std::endl;
file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;





_file_pkt._buf_used -= tmp->_header._mlen;
memmove(_file_pkt._buf, _file_pkt._buf + tmp->_header._mlen, sizeof(file_packet_t)-tmp->_header._mlen);
recv_head();
*/