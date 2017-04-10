#include "ClientSocket.h"
#include "RecvSocket.h"

ClientSocket::ClientSocket(string tmp)
	 :_file(NULL)  ,_file_pkt_sz(0)
	 ,_file_sz(0)  ,_pkt_send_sz(0)
	 ,final_(0)    ,_file_num(0)
	 ,_path_num(0) ,_root_path(tmp)
{	
	_path_num=explode(tmp, '/').size();
}

void ClientSocket::get_head()
{

	int time = _file_pkt._buf_used - _file_pkt._head_sz;
	for (int i = 0; i != time; ++i)
	{
		if (strncmp(_file_pkt._buf + i, (char *)&_file_pkt._head_id, sizeof(_file_pkt._head_id)) == 0){
			memmove(_file_pkt._buf, _file_pkt._buf + i, sizeof(file_packet_t)-i);
			_file_pkt._buf_used -= i;
			file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;
			if (_file_pkt._buf_used >= tmp->_header._mlen){
				get_path();
				return;
			}
			recv_path();
			return;
		}
	}
	memmove(_file_pkt._buf, _file_pkt._buf + time, sizeof(file_packet_t)-time);
	_file_pkt._buf_used -= time;
	recv_head();
}
void ClientSocket::get_path()
{
	file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;
	string need = tmp->fileinfo._fname;
	string realPath = _root_path + "/" + need;
	std::cout << realPath << std::endl;
	boost_rd_iterator end;

	for (boost_rd_iterator pos(realPath.c_str()); pos != end; pos++)
	{
		if (boost::filesystem::is_regular_file(*pos))
			_path.push_back(*pos);
	}
	_file_num = _path.size() - 1;
	send_start();
}
void ClientSocket::recv_head_handle(const boost::system::error_code ec, size_t size)
{
	
	std::cout << "头的大小  " << size << std::endl;
	if (!size)
	{
		this->final_ = 2;
		return;
	}
	_file_pkt._buf_used += size;
	if (_file_pkt._buf_used >= _file_pkt._head_sz){
		get_head();
		return;
	}
	recv_head();
}
void ClientSocket::recv_path_handle(const boost::system::error_code ec, size_t size)
{
	std::cout << "路径的大小  " << size << std::endl;
	if (!size)
	{
		this->final_ = 2;
		return;
	}
	_file_pkt._buf_used += size;
	file_packet_t * tmp = (file_packet_t *)_file_pkt._buf;

	if (_file_pkt._buf_used >= tmp->_header._mlen){
		get_path();
		return;
	}
	recv_path();
}
void ClientSocket::recv_head()
{
	std::cout << "等待接收头" << std::endl;
	this->_sock->async_read_some(buffer((void*)(_file_pkt._buf + _file_pkt._buf_used), sizeof(file_packet_t)),
		std::bind(&ClientSocket::recv_head_handle, this, std::placeholders::_1, std::placeholders::_2)
		);
}
void ClientSocket::recv_path()
{
	std::cout << "等待接收path" << std::endl;
	this->_sock->async_read_some(buffer((void*)(_file_pkt._buf + _file_pkt._buf_used), sizeof(file_packet_t)),
		std::bind(&ClientSocket::recv_path_handle, this, std::placeholders::_1,std::placeholders::_2)
		);

}

void ClientSocket::send_start()
{
	int tmp = read_m();
	if (!tmp && final_) {
		final_ = 2;
		_sock->close();
		return;
	}
	if (!tmp){
		final_ = 1;
		send_m();
	}
	send_m();
}

void ClientSocket::send_m()
{

	auto CallBack = [this](const boost::system::error_code ec, size_t size)
	{
		_pkt_send_sz += size;
		if (_pkt_send_sz >= _pkt._header._mlen){ //是否发完
			_pkt_send_sz = 0;
			send_start();
			return;
		}
		send_m();
	};
	_sock->async_write_some(buffer((void*)(&_pkt + _pkt_send_sz), _pkt._header._mlen - _pkt_send_sz),CallBack);
	//(char*)&_pkt+_pkt_send_sz,this->_pkt._header._mlen-_pkt_send_sz,0);
}

int ClientSocket::read_m()	//装订一个新包 调用时保证上个包发完了 
{
	if(!_file && _file_num < 0)  //所有文件发送完成
	{
		_pkt._header._mlen = sizeof(_pkt._header);
		_pkt._header._type = 2;
		//cout<<"完成"<<endl;
		return 0;
	}

	if(_file)	//上一个文件没发完
	{
		_pkt._header._type = 1;
		_pkt._header._mlen = fread(_pkt._mdata,sizeof(char),sizeof(_pkt._mdata),_file);
		_file_pkt_sz += _pkt._header._mlen;
		_pkt._header._mlen += sizeof(_pkt._header);

		if(_file_pkt_sz >= _file_sz)
		{
			--_file_num;
			fclose(_file);
			_file = NULL;
		}
		//cout<<"数据"<<endl;
		return 1;
	}
	
	//打包一个新文件//
	_pkt._header._type = 0;
	fopen_s(&_file,_path[_file_num].string().c_str(),"rb");
	
	_pkt.fileinfo._path_num = this->_path_num;
	sprintf_s(_pkt.fileinfo._fname,sizeof(_pkt.fileinfo._fname),_path[_file_num].string().c_str());

	_file_sz = boost::filesystem::file_size(_path[_file_num]);


	_pkt._header._mlen=sizeof(_pkt._header) + sizeof(_pkt.fileinfo._fname);
	//cout<<"包头"<<endl;
	return 1;
}
