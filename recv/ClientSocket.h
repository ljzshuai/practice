#pragma once
#include "file.h"
using Pclient = std::shared_ptr<ip::tcp::socket>;
class ClientSocket
{
public:
	string			_root_path;		   //����ĸ�Ŀ¼

	Pclient			_sock;
	file_packet_t	_pkt;				//Ҫ���͵İ�
	unsigned		_pkt_send_sz;		//��ǰ���Ѿ����͵Ĵ�С

	FILE *		    _file;				//���ڴ�����ļ�
	unsigned		_file_sz;			//���ڴ�����ļ��Ĵ�С
	unsigned		_file_pkt_sz;		//��ǰ�ļ��Ѿ�������Ĵ�С

	int			    _file_num;			//���跢�͵��ļ���
	int				final_;				//�Ƿ������ļ�ȫ������
	
	int				_path_num;			//�跢��Ŀ¼ǰ��·������

	recv_pkt		_file_pkt;			//������Ҫ���͵�Ŀ¼

	vector<boost::filesystem::path>		_path;	//��Ҫ���͵��ļ���·��


	int  read_m();			//װ��һ���°�
	void  send_start();
	void  send_m();

	void  recv_head();
	void  recv_head_handle(const boost::system::error_code ec, size_t size);
	void  recv_path();
	void  recv_path_handle(const boost::system::error_code ec, size_t size);
	void  get_head();
	void  get_path();//��ʼ��Ҫ���͵��ļ�Ŀ¼

	int  handle_recv(const boost::system::error_code ec, size_t size);

	ClientSocket(string path);
	~ClientSocket()
	{
		std::cout << "��ʧ��" << std::endl;
	}
private:
	ClientSocket();
};


