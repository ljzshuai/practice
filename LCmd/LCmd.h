#ifndef LCMD_H
#define LCMD_H
#include<string>
#include<vector>

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
#endif //LCMD_H
