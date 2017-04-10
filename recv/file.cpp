#include "file.h"
file_packet_t::file_packet_s()
{
	
	_header._id=999999;
	_header._type=3;
	_header._mlen=0;
	memset(_mdata,0,sizeof(_mdata));	
	
}

recv_pkt::recv_pkt(): _buf_used(0),_head_id(999999),_where(0)
{
	_buf=(char*) new file_packet_t;
	_buf_max=sizeof(file_packet_t);
	_head_sz=sizeof(file_packet_t::head);
}

recv_pkt::~recv_pkt()
{
	delete _buf;
}

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
