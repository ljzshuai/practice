#include "Client.h"
const vector<string> explode(const string& s, const char& c)
{
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
		if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}
Client::Client(io_service &ios,const string & path)
	:_pkt(nullptr), _file(nullptr)
	, _sock(ios), _path_save(path)
{

}

void Client::connect_m(ip::tcp::endpoint& ep,string path)
{
	_sock.connect(ep);
	recv_pkt date;
	file_packet_s * dd = (file_packet_s*)date._buf;
	dd->_header._mlen = sizeof(dd->_header) + sizeof(dd->fileinfo._path_num) +path.size()+1;
	memcpy(dd->fileinfo._fname,path.c_str(),path.size()+ 1);

	_sock.send(buffer((void*)dd,dd->_header._mlen));
	recv_head();
}

void Client::recv_head()//���հ�ͷ
{
	if (_file_pkt._buf_used >= _file_pkt._head_sz)
	{
		get_head();
		return;
	}
	auto CallBack = [this](const boost::system::error_code ec, size_t size)
	{
		std::cout << "ͷ�Ĵ�С  " << size << std::endl;
		if (!size) return;
		_file_pkt._buf_used += size;
		if (_file_pkt._buf_used >= _file_pkt._head_sz){
			get_head();
			return;
		}
		recv_head();
	};
	this->_sock.async_read_some(buffer((void*)(_file_pkt._buf + _file_pkt._buf_used)
								,sizeof(file_packet_t)-_file_pkt._buf_used)
								, CallBack);
}

void Client::get_head()//����Ƿ���ڰ�ͷ
{
	int time = _file_pkt._buf_used - _file_pkt._head_sz;
	for (int i = 0; i != time; ++i)
	{
		if (strncmp(_file_pkt._buf + i, (char *)&_file_pkt._head_id, sizeof(_file_pkt._head_id)) == 0){
			memmove(_file_pkt._buf, _file_pkt._buf + i, sizeof(file_packet_t)-i);
			_file_pkt._buf_used -= i;
			_pkt = (file_packet_t *)_file_pkt._buf;
			if (_file_pkt._buf_used >= _pkt->_header._mlen){
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

void Client::recv_date()//���հ�ͷ��������
{
	auto CallBack = [this](const boost::system::error_code ec, size_t size)
	{
		std::cout << "���ݴ�С  " << size << std::endl;
		if (!size) return;
		_file_pkt._buf_used += size;

		if (_file_pkt._buf_used >= _pkt->_header._mlen){
			get_date();
			return;
		}
		recv_date();
	};

	this->_sock.async_read_some(buffer((void*)(_file_pkt._buf + _file_pkt._buf_used)
		, sizeof(file_packet_t)-_file_pkt._buf_used)
		, CallBack);
		
}

void Client::get_date()//����type��������
{
	switch (_pkt->_header._type)
	{
	case 0:
		type0();return;
	case 1:
		type1();return;
	case 2:
		type2();return;
	default:
		return;
	}
}

void Client::type0()//����Ŀ¼���ļ�
{
	if (_file)
	{
		fclose(_file);
		_file = nullptr;
	}

	string temp_str;
	vector<string>name(explode(_pkt->fileinfo._fname, '/'));

	for (int i = _pkt->fileinfo._path_num; i != name.size(); ++i)
		temp_str += name[i] + '/';	
	temp_str.erase(temp_str.end() - 1);

	temp_str = string(_path_save) + "/" + temp_str;

	boost::filesystem::create_directories(boost::filesystem::path(temp_str.c_str()).parent_path());

	fopen_s(&_file, temp_str.c_str(), "wb+");
	_file_pkt._buf_used -= _pkt->_header._mlen;
	memmove(_file_pkt._buf, _file_pkt._buf + _pkt->_header._mlen, sizeof(file_packet_t)-_pkt->_header._mlen);

	cout << "��ͷ" << endl;
	//һ����������� ������һ����
	recv_head();
}

void Client::type1()
{
	if (!_file)
		return;
	fwrite(_pkt->_mdata, sizeof(char), _pkt->_header._mlen - sizeof(_pkt->_header), _file);
	_file_pkt._buf_used -= _pkt->_header._mlen;
	memmove(_file_pkt._buf, _file_pkt._buf + _pkt->_header._mlen, sizeof(file_packet_t)-_pkt->_header._mlen);
	cout << "����" << endl;
	//һ����������� ������һ����
	recv_head();
}

void Client::type2()
{
	fclose(_file);
	_sock.close();
	cout << "����" << endl;
	system("pause");
}