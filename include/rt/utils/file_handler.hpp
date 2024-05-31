#ifndef RT_RESSOURCE_LOADER_H
#define RT_RESSOURCE_LOADER_H

#include <string>

struct FileHandler
{
    static std::string get_file_content(const char* path);
};

#endif // RT_RESSOURCE_LOADER_H