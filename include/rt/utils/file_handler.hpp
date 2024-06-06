#ifndef RT_FILE_HANDLER_H
#define RT_FILE_HANDLER_H

#include <rt/utils/image.hpp>

#include <fstream>
#include <ios>
#include <string>

namespace rt
{

struct FileHandler
{
    static std::string get_file_as_text(const char* path);
    static Image get_file_as_image(const char* path);

  private:
    static std::ifstream open_file_stream(const char* path, std::ios_base::openmode open_mode = std::ios_base::in);
};

} // namespace rt

#endif // RT_FILE_HANDLER_H