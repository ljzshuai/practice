#include "RecvSocket.h"
#include "ClientSocket.h"
void RecvSocket::accept_start(string path) //创建client SOCKET 开始发送
{
	std::shared_ptr<ClientSocket> client= make_shared<ClientSocket>(path);
	Pclient tmp = make_shared<ip::tcp::socket>(_accept.get_io_service());
	client->_sock = tmp;
	clients.push_back(client);
	auto callback = [this, client,path](const boost::system::error_code ec){
		if (ec)
			return;

		client->recv_head();
		accept_start(path);
	};
	_accept.async_accept(*client->_sock, callback);
}

void RecvSocket::clean()
{
	for (auto i = clients.begin(); i != clients.end(); )
	{
		if ((*i)->final_ == 2)
			i = clients.erase(i);
		else
			++i;
	}
}

RecvSocket::RecvSocket(ip::tcp::endpoint&ep, io_service& ios)
	:_accept(ios, ep)
{
	
}
