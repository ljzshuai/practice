#pragma once
#include "file.h"
#include "ClientSocket.h"
class RecvSocket
{
public:
	RecvSocket(ip::tcp::endpoint& ep, io_service&);
	~RecvSocket() = default;

	void accept_start(string path);
	void clean();
private:
	ip::tcp::acceptor		_accept;
	vector<std::shared_ptr<ClientSocket>> clients;
};