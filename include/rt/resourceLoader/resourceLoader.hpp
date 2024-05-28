#ifndef RT_RESSOURCE_LOADER_H
#define RT_RESSOURCE_LOADER_H

#include <string>

class ResourceLoader
{
  public:
    static std::string read_file(const char* path);
};

#endif // RT_RESSOURCE_LOADER_H