#include <Engine/IO/textFileBasic.hpp>
#include <fstream>
#include <sstream>


bool anim::ios::TextFileBasic::write(std::string* buffer, const char* path)
{
	std::scoped_lock lock(mCritSection);
	std::ofstream ostr;
	
	if (path == nullptr || buffer == nullptr)
		return false;

	ostr.open(path);

	if (!ostr.is_open())
	{
		LOG_MESSAGE("[TextFileBasic] Cannot write to: " << path);
		return false;
	}

	ostr << buffer;
	ostr.close();

	return true;
}

bool anim::ios::TextFileBasic::read(std::string* buffer, const char* path)
{
	std::scoped_lock lock(mCritSection);
	std::ifstream istr;

	if (path == nullptr || buffer == nullptr)
		return false;

	istr.open(path);
	if (!istr.is_open())
	{
		LOG_MESSAGE("[TextFileBasic] Cannot read from: " << path);
		return false;
	}

	std::stringstream sstr;
	sstr << istr.rdbuf();

	istr.close();
	*buffer = sstr.str();

	return true;
}