#pragma once
#include "file.h"
using Pclient = std::shared_ptr<ip::tcp::socket>;
class ClientSocket
{
public:
	string			_root_path;		   //共享的根目录

	Pclient			_sock;
	file_packet_t	_pkt;				//要发送的包
	unsigned		_pkt_send_sz;		//当前包已经发送的大小

	FILE *		    _file;				//正在打包的文件
	unsigned		_file_sz;			//正在打包的文件的大小
	unsigned		_file_pkt_sz;		//当前文件已经被打包的大小

	int			    _file_num;			//还需发送的文件数
	int				final_;				//是否所有文件全部发完
	
	int				_path_num;			//需发送目录前的路径长度

	recv_pkt		_file_pkt;			//接收需要发送的目录

	vector<boost::filesystem::path>		_path;	//需要发送的文件的路径


	int  read_m();			//装订一个新包
	void  send_start();
	void  send_m();

	void  recv_head();
	void  recv_head_handle(const boost::system::error_code ec, size_t size);
	void  recv_path();
	void  recv_path_handle(const boost::system::error_code ec, size_t size);
	void  get_head();
	void  get_path();//初始化要发送的文件目录

	int  handle_recv(const boost::system::error_code ec, size_t size);

	ClientSocket(string path);
	~ClientSocket()
	{
		std::cout << "消失了" << std::endl;
	}
private:
	ClientSocket();
};


