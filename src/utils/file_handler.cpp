#include <rt/utils/file_handler.hpp>

#include <filesystem>
#include <fstream>

std::string FileHandler::get_file_content(const char* path)
{
    std::filesystem::path path_object = std::filesystem::absolute(path);
    std::ifstream file = std::ifstream(path);
    std::ostringstream file_content;
    std::string line;

    if (!file.is_open())
    {
        std::string error_message = std::string("File not found: ") + path_object.string() + "\n";
        throw std::runtime_error(error_message.c_str());
    }

    while (std::getline(file, line))
    {
        file_content << line << "\n";
    }

    return file_content.str();
}