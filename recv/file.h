#pragma once
#include<iostream>
#include<memory>
#include<stdint.h>
#include<stdint.h>
#include<string>
#include<cstring>
#include<vector>
#include<direct.h>
#include<io.h>
#include<direct.h>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<fstream>
#include<sys/stat.h>
#include<assert.h>
#include<stdio.h>
#include<boost/filesystem.hpp>
#include<boost\asio.hpp>

#define invalid_socket		(unsigned)(~0)

//using namespace std;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::cin;
using std::endl;
using namespace boost::asio;

#define PACKET_MLEN			8388608
typedef long long			llong;
typedef boost::filesystem::recursive_directory_iterator boost_rd_iterator;

//#pragma comment(lib,"ws2_32.lib")


/*
	���ݽṹ--��
	_header ��������������ͺʹ�С
	union   ����ļ��������ļ�����
*/
#pragma  pack(1)
typedef struct file_packet_s
{
	struct head
	{
		int				_id;	// ��֤
		int				_type;	// =0 �ļ���; =1 �ļ�����; =2 �����ļ��������
		unsigned		_mlen;	// ���Ĵ�С
	}_header;
	union 
	{
		struct 
		{
			int		_path_num; //·������(��boostʹ��)
			char	_fname[MAX_PATH];
		}fileinfo;
		char	_mdata[PACKET_MLEN];
	};
	file_packet_s();
}file_packet_t;


struct recv_pkt{	
	unsigned	_buf_max;		//��������С
	char*		_buf;			//���հ�
	unsigned	_buf_used;		//buf�Ѿ�ʹ�õĴ�С
	unsigned	_head_id;		//��֤
	unsigned	_where;			//���еڼ���
	unsigned	_head_sz;		//��ͷ��С
	recv_pkt();
	~recv_pkt();
};

