#ifndef _ANIM_IO_TEXT_FILE_BASIC_
#define _ANIM_IO_TEXT_FILE_BASIC_

#include <Core/Types/BasicTypes.hpp>

namespace anim::ios 
{

class TextFileBasic
{
public:
    TextFileBasic() = default;
    ~TextFileBasic() = default;

    bool write(std::string* buffer, const char* path);
	bool read (std::string* buffer, const char* path);

private: 
    std::mutex mCritSection;
};
}
#endif