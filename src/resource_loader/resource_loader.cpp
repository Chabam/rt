#include <rt/resource_loader/resource_loader.hpp>

#include <filesystem>
#include <fstream>

std::string ResourceLoader::read_file(const char* path)
{
    std::filesystem::path pathObject = std::filesystem::absolute(path);
    std::ifstream file = std::ifstream(path);
    std::ostringstream fileContent;
    std::string line;

    if (!file.is_open())
    {
        std::string error_message = std::string("File not found: ") + pathObject.string() + "\n";
        throw std::runtime_error(error_message.c_str());
    }

    while (std::getline(file, line))
    {
        fileContent << line << "\n";
    }

    return fileContent.str();
}