#include "LCmd.h"
#include <cstdio>

namespace LJZ{

LCmd::LCmd() :result_num_(0)
	, result_()
	, error_(NOERROR)
{
}

bool LCmd::setCmd(const std::string& cmd)
{
	if (cmd.empty()){
		error_ = NO_INPUT;
		return false;
	}
	if (cmd.size() > 1024){
		error_ = INPUT_VOER_STR_LENGTH;
		return false;
	}
	char buf_ps[1024]{0};
	FILE *ptr = nullptr;

	std::string tmp;
	if ((ptr = Lpopen(cmd.c_str(), "r")) != nullptr)
	{
		while (fgets(buf_ps, 1024, ptr) != nullptr)
		{
			tmp += buf_ps;
		}
		_pclose(ptr);
		result_.push_back(tmp);
		++result_num_;
		ptr = nullptr;
		return true;
	}
	return false;
}

std::string LCmd::getLastResult()
{
	return result_.back();
}

std::string LCmd::getResult(const unsigned&countdown)
{
	if (countdown == 0)
	{
		error_ = INPUT_ZERO_NUM;
		return "";
	}
	if (countdown > result_.size())
	{
		error_ = INPUT_VOER_NUM;
		return "";
	}
	return result_[result_.size() - countdown];
}

void LCmd::clear()
{
	result_.swap(std::vector<std::string>());
	result_num_ = 0;
}

std::string LCmd::getLastError()
{
	switch (error_)
	{
	case NOERROR:
		return "no error";
	case INPUT_ZERO_NUM:
		return "no countdown zero";
	case INPUT_VOER_NUM:
		return "getResult() input too big";
	case INPUT_VOER_STR_LENGTH:
		return "cmd too long";
	case NO_INPUT:
		return "no cmd";
	default:
	return "unknow error";
	}
}

LCmd::~LCmd()
{
}

}//end namespace LJZ