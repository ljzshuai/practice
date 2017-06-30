/**************************************************************************

Copyright:liujiazhi

Author: liujiazhi

Date:2017-6-29 

Description:获取cmd命令数据

注意：无法分辨cmd命令错误还是cmd命令启动了一个程序
	  出现上述情况会获取的结果为空字符串，且错误提
	  示为无错误
**************************************************************************/

#ifndef LCMD_H
#define LCMD_H

#include<cstdio>
#include<string>
#include<vector>

#ifdef _WIN32
#define Lpopen _popen
#else
#define Lpopen popen
#endif

namespace LJZ{

enum LCMD_ERROR{
	NOERROR,
	INPUT_ZERO_NUM,
	INPUT_VOER_NUM,
	INPUT_VOER_STR_LENGTH,
	NO_INPUT,
	ERROR_COUNT
};

class LCmd
{
public:
	LCmd();
	~LCmd();
	bool setCmd(const std::string&);
	std::string getLastResult();
	std::string getResult(const unsigned & countdown);
	inline unsigned resultSize(){ return result_.size(); }
	void clear();
	std::string getLastError();
private:
	int result_num_;
	LCMD_ERROR error_;
	std::vector<std::string> result_;
};

}//end namespace LJZ
#endif //LCMD_H
