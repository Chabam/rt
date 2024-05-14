#pragma once
#include <string>

class ResourceLoader
{
  public:
    static std::string read_file(const char* path);
};