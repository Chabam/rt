#ifndef RT_FILE_HANDLER_H
#define RT_FILE_HANDLER_H

#include <string>

struct FileHandler
{
    static std::string get_file_content(const char* path);
};

#endif // RT_FILE_HANDLER_H